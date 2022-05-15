#include "newsaggregator.h"
#include <string>
#include <iostream>
#include "answer2.h"

using namespace std;

WebPage webPage;

void part2();

void insertNewsItem(string const &title, string const &text, string const &author, string const &name,
                    string const &webpage) {
    webPage.insertNewsItem(title, text, author, name, webpage);
}

string getContent(string const &sourceUrl, string const &title) {
    return webPage.getContent(sourceUrl, title);
}

std::string const& getHottestCategory() {
    return webPage.getHottestCategory();
}


void usage1() {
    auto title = "Something Happened";
    auto text = "London is a city where things happen all the time";
    auto author = "A random stranger";
    auto categoryName = "London News";
    auto sourceWebpage = "http://www.blameberg.com";
    insertNewsItem(title, text, author, categoryName, sourceWebpage);
}


void usage2() {
    auto sourceWebpage = "http://www.blameberg.com";
    auto title = "Something Happened";
    string content = getContent(sourceWebpage, title);
    cout << content << endl;
}


void usage3() { //
    auto categoryName = getHottestCategory();
    cout << categoryName << endl;
}


void part2() {
    auto basket = Basket<Fruit,30>();
    basket.add(new RedApple(95, 7, "Gala", 0.8));
    basket.add(new MixedApple(85, 8, "Cox", 0.6));
    basket.add(new Pear(140, 2, "Ambrosia", true));

    // this basket only holds fit-for-cell and isPremium fruit
    auto goodBasket = Basket<Fruit,10>();
    while (!basket.isEmpty() && !goodBasket.isFull()) {
        cout << "basket now has: " << endl;
        basket.print();
        cout << "good basket now has: " << endl;
        goodBasket.print();
        cout << endl;
        Fruit* fruit = basket.popFirst();
        if (fruit->isPremium() && fruit->isFitForSale()) {
            goodBasket.add(fruit);
        } else { delete fruit; }
    }
}


int main(int argc, char* argv[]) {
    // part1
    usage1();
    usage2();
    usage3();
    cout << endl;
    // part2
    part2();

    return 0;
}


