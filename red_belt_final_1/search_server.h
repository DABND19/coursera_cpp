#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
using namespace std;

/*
  document_input содержит не более 50000 документов

  каждый документ содержит не более 1000 слов

  общее число различных слов во всех документах не превосходит 15000

  максимальная длина одного слова — 100 символов, 
  слова состоят из строчных латинских букв и разделены одним или несколькими пробелами

  query_input содержит не более 500 000 запросов, каждый запрос содержит от 1 до 10 слов.
*/

/*
  Построение обратного индекса устроено слудющим образом:
  1) Мы храним каждый документ в docs
  2) Каждый документ разбивается на слова, и для каждого слова мы имеем
  список документов, в котором оно содержится. Все это хранится в index.
  Такой процесс и называется построением обратного индекса.
*/

class InvertedIndex
{
public:
  struct Item
  {
    size_t docid;
    size_t hitcount;
  };

  void Add(string &&document);
  vector<Item> Lookup(const string &word) const;

  const string &GetDocument(size_t id) const
  {
    return docs[id];
  }

  size_t GetDocsNum() const
  {
    return docs.size();
  }

private:
  map<string, vector<Item>> index;
  vector<string> docs;
};

const vector<InvertedIndex::Item> EMPTY_LOOKUP = {};

class SearchServer
{
public:
  SearchServer() = default;
  explicit SearchServer(istream &document_input);
  void UpdateDocumentBase(istream &document_input);
  void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
  InvertedIndex index;
};
