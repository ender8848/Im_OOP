//
// Created by 85378 on 5/7/2022.
//

#ifndef OOP2019_V2_NEWSAGGREGATOR_H
#define OOP2019_V2_NEWSAGGREGATOR_H

#define MAX_CATEGORY_NUM 500
#define MAX_NEWS_PER_SOURCE 1000
#define MAX_SOURCE_NUM 100

#include <string>
#include <map>
#include <stdexcept>

class News;
class Source;
class Category;
class WebPage;

class Category {
    std::string name; // key
    Category * parent;
    int counter = 0;
public:
    friend class News;
    Category() = default;
    Category(std::string const& name, Category * parent = nullptr):name(name), parent(parent) {}
    Category& operator=(const Category& other) {
        name = other.name;
        parent = other.parent;
        counter = other.counter;
        return *this;
    }

    std::string const& getName() const { return name; }
    int getCounter() const { return counter; }


    void plus() {
        ++counter;
        if (parent != nullptr) parent->plus();
    }
};

class News {
private:
    std::string title;
    std::string content;
    std::string author;
    Category * pCategory = nullptr;
    int mutable counter = 0;

public:
    News() = default;
    News(std::string const& title, std::string const& content, std::string const& author, Category* pCategory):
            title(title), content(content), author(author), pCategory(pCategory) {}
    News& operator=(const News& other) {
        this->title = other.title;
        this->content = other.content;
        this->author = other.author;
        this->pCategory = other.pCategory;
        this->counter = other.counter;
        return *this;
    }

    std::string const& getTitle() const {
        return this->title;
    }

    std::string const& getContent() const {
        ++counter;
        if (pCategory != nullptr) pCategory->plus();
        return this->content;
    }

};

class Source {
    std::string url; // key
    News news[MAX_NEWS_PER_SOURCE];
    int size = 0;
public:
    Source() = default;
    Source(std::string const& url) : url(url) {}
    Source& operator=(Source const& other) {
        this->url = other.url;
        return *this;
    }

    void addNews(std::string const& title, std::string const& content, std::string const& author,
                 Category* pCategory) {
        if (size >= MAX_NEWS_PER_SOURCE) { throw std::runtime_error("Source is full"); }
        news[size++] = News(title, content, author, pCategory);
    }

    std::string const& getContent(const std::string &title) const {
        for (int i = 0; i < size; i++) {
            if (news[i].getTitle() == title) {
                return news[i].getContent();
            }
        }
    }
};


class WebPage {
private:
    std::map<std::string, Source> sources;
    std::map<std::string, Category> categories;

public:
    WebPage() = default;

    void insertNewsItem(std::string const& title, std::string  const& content, std::string const& author,
                        std::string const& categoryName, std::string const& sourceUrl) {
        if (sources.find(sourceUrl) == sources.end()) { addSource(sourceUrl); }
        if (categories.find(categoryName) == categories.end()) { addCategory(categoryName); }
        Category& category = categories[categoryName];
        sources[sourceUrl].addNews(title, content, author, &category);
    }

    void addCategory(std::string const& categoryName, std::string const& parentCategoryName = "") {
        if (categories.find(categoryName) != categories.end()) {
            throw std::runtime_error("Category already exists");
        }
        if (parentCategoryName != "" && categories.find(parentCategoryName) == categories.end()) {
            throw std::runtime_error("Parent category does not exist");
        }
        if (parentCategoryName == "") {
            categories[categoryName] = Category(categoryName);
        } else {
            categories[categoryName] = Category(categoryName, &categories[parentCategoryName]);
        }
    }

    void addSource(std::string const& url) {
        if (sources.find(url) != sources.end()) {
            throw std::runtime_error("Source already exists");
        }
        sources[url] = Source(url);
    }

    std::string const& getContent(std::string const& sourceUrl, std::string const& title) {
        if (sources.find(sourceUrl) == sources.end()) {
            throw std::runtime_error("Source does not exist");
        }
        return sources[sourceUrl].getContent(title);
    }

    std::string const& getHottestCategory() {
        int max = -1;
        std::string hottest;
        for (auto it = categories.begin(); it != categories.end(); ++it) {
            if (it->second.getCounter() > max) {
                hottest = it->first;
                max = it->second.getCounter();
            }
        }
        return categories[hottest].getName();
    }
};

#endif //OOP2019_V2_NEWSAGGREGATOR_H
