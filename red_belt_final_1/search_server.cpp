#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

vector<string> SplitIntoWords(const string &line)
{
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream &document_input)
{
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input)
{
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document);)
  {
    new_index.Add(move(current_document));
  }

  swap(index, new_index);
}

void SearchServer::AddQueriesStream(
    istream &query_input, ostream &search_results_output)
{
  vector<size_t> docid_count(index.GetDocsNum());
  vector<size_t> search_results_indices(index.GetDocsNum());

  for (string current_query; getline(query_input, current_query);)
  {
    const auto words = SplitIntoWords(current_query);

    fill(docid_count.begin(), docid_count.end(), 0);
    for (const auto &word : words)
    {
      for (const auto [docid, hitcount] : index.Lookup(word))
      {
        docid_count[docid] += hitcount;
      }
    }

    iota(search_results_indices.begin(), search_results_indices.end(), 0);

    auto top5_it = Head(search_results_indices, 5).end();

    partial_sort(search_results_indices.begin(),
                 top5_it,
                 search_results_indices.end(),
                 [&docid_count](size_t lhs, size_t rhs) {
                   return make_pair(docid_count[lhs], rhs) > make_pair(docid_count[rhs], lhs);
                 });

    search_results_output << current_query << ':';
    for (auto docid : Head(search_results_indices, 5))
    {
      auto hitcount = docid_count[docid];
      if (hitcount != 0)
      {
        search_results_output << " {"
                              << "docid: " << docid << ", "
                              << "hitcount: " << hitcount << '}';
      }
    }
    search_results_output << endl;
  }
}

void InvertedIndex::Add(string &&document)
{
  docs.emplace_back(document);

  /*
    Здесь используется следующая гипотеза:
    Индекс только что добавленного документа будет
    больше, чем индекс предыдущих. Это значит, что
    последовательность docid, лежащая в каждом элементе
    словаря index будет возрастающей.
  */

  const size_t docid = docs.size() - 1;
  for (const auto &word : SplitIntoWords(document))
  {
    auto &doc_list = index[word];
    if (doc_list.empty())
    {
      doc_list.emplace_back(Item{docid, 1});
    }
    else
    {
      auto &last = doc_list.back();
      if (last.docid != docid)
      {
        doc_list.emplace_back(Item{docid, 1});
      }
      else
      {
        last.hitcount++;
      }
    }
  }
}

vector<InvertedIndex::Item> InvertedIndex::Lookup(const string &word) const
{
  try
  {
    return index.at(word);
  }
  catch (const out_of_range &)
  {
    return EMPTY_LOOKUP;
  }
}
