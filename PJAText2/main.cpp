#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstring>
#include <set>
#include <sstream>


std::stringstream output;

/**
 * funkcja przedstawia co mozna zrobic w programie
 * wyswietla komunikat o programie
 */
auto prezentacja(){
    std::cout << "|| Witaj, jest to program PJAText2, do ktorego podamy takie flagi jak: "<< '\n' <<
                "-f Sprawdzi czy plik jest prawidlowy" << '\n' <<
                "-n Wyswietli liczbe lini z pliku" << '\n' <<
                "-d Wyswietli liczbe cyfr z pliku" << '\n' <<
                "-dd Wyswietli liczbe licz z pliku" << '\n' <<
                "-c Wyswietli liczbe znakow z pliku" << '\n' <<
                "-wc -c Wyswietli liczbe znakow wraz z bialymi z pliku" << '\n' <<
                "-w Wyswietli liczbe slow z pliku" << '\n' <<
                "-s Wyswietli posortowane slowa w kolejnosci alfabetyczne lub w zaleznosci od dlugosci slow" << '\n' <<
                "-l -s Wyswietli posortowane slowaw zaleznosci od dlugosci slow" << '\n' <<
                "-rs Wyswietli odwrotnie posortowane slowa w kolejnosci alfabetyczne lub w zaleznosci od dlugosci slow" << '\n' <<
                "-l -rs Wyswietli odwrotnie posortowane slowaw zaleznosci od dlugosci slow" << '\n' <<
                "-a Wyswietli slowa z pliku ktore sa anagramami slow podanych w konsoli" << '\n' <<
                "-p Wyswietli slowa z pliku ktore sa palindromami slow podanych w konsoli" << '\n' <<
                "-o Pozwola zdecydowac czy wyswietlic informacje w konsoli czy zapisac wszystko do pliku" << '\n' <<
                "-i Pozwala zczytac plik z flagami i wyswietlic odpowiedni komunikat" << std::endl;
}

/**
 *  funkcja check sprawdza czy plik istnieje i czy jest poprawny
 * @param v : jest to nazwa pliku
 * jeżeli plik jest poprawny to nic nie wyświetli, jezeli plik nie jest poprawny to zapisze odpowiedni komunikat do output
 */
auto check(const std::string& v){
    auto file = std::fstream(v);
    if(file){
    } else{
        output << "Podany plik jest bledny" << std::endl;
    }
}

/**
 * funkcja newlines liczy ilosc lini w pliku
 * @param v : jest to nazwa pliku
 * komunikat o ilosci lini w pliku jest zapisywany do output
 */
auto newlines(const std::string& v){
    auto x = 0;
    auto file = std::fstream(v);
    check(v);
    for(auto line = std::string(); std::getline(file, line);){
        x++;
    }
    output << "Ilosc lini w pliku " << v << ": " << x << std::endl;
}

/**
 * funkcja zlicza ilosc cyfr
 * @param v : jest to nazwa pliku
 * komunikat o ilosci cyfr w pliku jest zapisywany do output
 */
auto digits(const std::string& v){
    auto file = std::fstream(v);
    check(v);
    auto x = 0;
    for(auto word = std::string(); file >> word;){
        for(auto i : word){
            if(isdigit(i)){
                x++;
            }
        }
    }
    output << "Ilosc cyfr w pliku " << v << ": " << x << std::endl;
}

/**
 *  funkcja sprawdza danego stringa czy jest liczba
 * @param str
 * isRealNumber zwraca tylko liczby
 */
bool isRealNumber(std::string& str){
    auto it = str.begin();
    bool decimalPoint = false;
    int minSize = 0;
    if(str.size()>0 && (str[0] == '-' || str[0] == '+')){
        it++;
        minSize++;
    }
    while(it != str.end()){
        if(*it == '.'){
            if(!decimalPoint) decimalPoint = true;
            else break;
        }else if(!std::isdigit(*it)){
            break;
        }
        ++it;
    }
    return str.size()>minSize && it == str.end();
}
/**
 * funkcja liczy ilosc liczb w pliku
 * @param v : jest to nazwa pliku
 * Komunikat o ilosci liczb jest zapisywany w output
 */
auto numbers(const std::string& v){
    auto file = std::fstream(v);
    check(v);
    int x = 0;
    for(auto word = std::string(); file >> word;)
        if(isRealNumber(word)) {
            x++;
        }

    output << "Ilosc liczb w pliku " << v << ": " << x << std::endl;
}

/**
 * funkcja liczy ilosc znakow w pliku
 * @param v : jest to nazwa pliku
 * @param f jest to flaga ktora modyfikuje liczenie znakow (zalicza tez biale znaki)
 * Komunikat o ilosci znakow jest zapisywany w output
 */
auto chars(const std::string& v, const std::string& f){
    auto x = 0;
    auto file = std::fstream(v);
    check(v);
    if(f == "-wc" || f == "--white"){
        std::string tmp;
        while(getline(file, tmp)){
            for(char c : tmp)
                x++;
        }
        output << "Ilosc znakow (z bialymi) w pliku " << v << ": " << x << std::endl;
    }else{
        for(auto word = std::string(); file >> word;){
            for(auto i : word){
                x++;
            }
        }
        output << "Ilosc znakow w pliku " << v << ": " << x << std::endl;
    }
}

/**
 * funcka liczy ilosc slow w pliku
 * @param v : jest to nazwa pliku
 * Komunikat o ilosci slow jest zapisywany w output
 */
auto words(const std::string& v){
    auto x = 0;
    auto file = std::fstream(v);
    check(v);
    for(auto word = std::string(); file >> word;){
        x++;
    }
    output << "Ilosc slow w pliku " << v << ": " << x << std::endl;
}

/**
 * funkcja porownuje dlugosc stringow
 * @param left pierwszy string
 * @param right drugi string
 * funkcja zwraca dluzsze slowo
 */
static bool comparator(const std::string& left, const std::string& right){
    return left.size() < right.size();
}

/**
 *  funkcja sortuje slowa w pliku
 * @param v : jest to nazwa pliku
 * @param f jest to flaga ktora modyfikuje dzialanie sorted (sortuje po dlugosci slow)
 * Posortowane slowa zapisywane sa do output
 */
auto sorted(const std::string& v, const std::string& f) {
    auto vec = std::vector<std::string>();
    auto file = std::fstream(v);
    check(v);
    for (auto word = std::string(); file >> word;) {
        vec.push_back(word);
    }
    if(f == "-l" || f == "--by-length")
        std::sort(vec.begin(), vec.end(), comparator);
    else
        std::sort(vec.begin(), vec.end());
    for (auto i : vec)
        output << i << ' ';
    output << std::endl;
}

/**
 *  funcka sortuje w odwrotny sposob slowa
 * @param v : jest to nazwa pliku
 * @param f jest to flaga ktora modyfikuje dzialanie reverse_sorted (sortuje po dlugosci slow)
 * Posortowane slowa zapisywane sa do output
 */
auto reverse_sorted(const std::string& v, const std::string& f){
    auto vec = std::vector<std::string>();
    auto file = std::fstream(v);
    check(v);
    for(auto word = std::string(); file >> word;){
        vec.push_back(word);
    }
    if(f == "-l" || f == "--by-length"){
        std::sort(vec.begin(), vec.end(), comparator);
        std::reverse(vec.begin(), vec.end());
    }else {
        std::sort(vec.begin(), vec.end());
        std::reverse(vec.begin(), vec.end());
    }
    for (auto i : vec) {
        output << i << ' ';
    }
    output << std::endl;
}

/**
 * funkcja szuka anagramow podanych slow po fladze -a z pliku
 * @param v : jest to nazwa pliku
 * @param vec vector slow po fladze -a
 * Znalezione slowa zapisywane sa do output
 */
auto anagrams(const std::string& v, const std::vector<std::string>& vec){
    auto file = std::fstream(v);
    check(v);
    std::set<std::pair<std::string, std::string>> words;
    for(auto i : vec){
        if(i[0] == '-'){
            output << "Flaga po -a" << std::endl;
            return;
        }
    }
    for(auto word = std::string(); file >> word;){
        auto original_word = word;
        sort(word.begin(), word.end());
        words.insert({word, original_word});
    }

    bool wypisane[words.size()];
    for(int i = 0 ; i < words.size(); i++)
        wypisane[i] = false;
    for(auto el : vec){
        sort(el.begin(), el.end());
        int i = 0;
        for(auto j : words){
            if(j.first == el){
                wypisane[i] = true;
            }
            i++;
        }
    }
    int i = 0;
    for(auto el : words){
        if(wypisane[i]){
            output << el.second << ' ';
        }
        i++;
    }
    output << std::endl;

}

/**
 * funkcja sprawdza czy string jest palindromem
 * @param s string do sprawdzenia czy jest palindromem
 * @return zwraca true jak slowo jest palindromem, jake nie jest zwraca false
 */
auto czyPalindrom(std::string s){
    int j = s.size() - 1;
    for(int i = 0; i < s.size(); i++){
        if(s[i] != s[j]){
            return false;
        }
        j--;
    }
    return true;
}

 /**
  * funkcja szuka slow ktore sa palindromami i sa podane po fladze -p
  * @param v : jest to nazwa pliku
  * @param vec vector slow po fladze -p
  * Znalezione slowa zapisywane sa do output
  */
auto palindromes(std::string v, std::vector<std::string> vec){
    auto file = std::fstream(v);
     check(v);
    auto pal = std::set<std::string>();
    for(auto i : vec){
        if(i[0] == '-'){
            output << "Flaga po -p" << std::endl;
            return;
        }
    }
    for(auto word = std::string(); file >> word;) {
        if(czyPalindrom(word)){
            pal.insert(word);
        }
    }


    for(auto i : pal){
        for(auto j : vec){
            if(i == j){
                output << i << ' ';
                break;
            }
        }
    }

    output << std::endl;
}

//wlasna flaga jest to -wc a jej alias to --white
//flaga modyfikuje dzialanie flagi -c i powoduje, ze ta flaga liczy kazdy znam rowniez bialy


int main( int argc, char ** argv ){
    std::vector<std::string> flagi;
    std::string name;
    std::string output_file = "";
    if(argc > 1){
        if(strcmp(argv[1], "--help") == 0 || argv[1][0] != '-'){
            prezentacja();
        }else if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--input") == 0){
            if(argc > 2){
                auto file = std::ifstream(argv[2]);
                if(file){
                    for (auto word = std::string(); file >> word;) {
                        flagi.push_back(word);
                    }
                }else{
                    std::cout << "Nie ma takiego pliku" << std::endl;
                }
            }else{
                std::cout << "Nie podales pliku" << std::endl;
            }
            if(argc > 3){
                std::cout << "sa flagi po -i" << std::endl;
            }
        }
    }else if(argc == 1) {
        prezentacja();
    }
    if(flagi.size() == 0){
        for(int i = 1; i < argc; i++){
            flagi.push_back(argv[i]);
        }
    }
    for( int i = 0; i < flagi.size(); i++ ) {
        if(strcmp(flagi[i].c_str(), "-f") == 0 || strcmp(flagi[i].c_str(), "--file") == 0){
            if(i+1 < flagi.size()){
                name = flagi[i+1];
                check(name);
            }else{
                output << "Brakuje sciezki do pliku";
            }
        }
        else if(strcmp(flagi[i].c_str(), "-n") == 0 || strcmp(flagi[i].c_str(), "--newlines") == 0){
            newlines(name);
        }
        else if(strcmp(flagi[i].c_str(), "-d") == 0 || strcmp(flagi[i].c_str(), "--digits") == 0){
            digits(name);
        }
        else if(strcmp(flagi[i].c_str(), "-dd") == 0 || strcmp(flagi[i].c_str(), "--numbers") == 0){
            numbers(name);
        }
        else if(strcmp(flagi[i].c_str(), "-c") == 0 || strcmp(flagi[i].c_str(), "--chars") == 0){
            chars(name, flagi[i-1]);
        }
        else if(strcmp(flagi[i].c_str(), "-w") == 0 || strcmp(flagi[i].c_str(), "--words") == 0){
            words(name);
        }
        else if(strcmp(flagi[i].c_str(), "-s") == 0 || strcmp(flagi[i].c_str(), "--sorted") == 0){
            sorted(name, flagi[i-1]);
        }
        else if(strcmp(flagi[i].c_str(), "-rs") == 0 || strcmp(flagi[i].c_str(), "--reverse-sorted") == 0){
            reverse_sorted(name, flagi[i-1]);
        }
        else if(strcmp(flagi[i].c_str(), "-a") == 0 || strcmp(flagi[i].c_str(), "--anagrams") == 0){
            std::vector<std::string> vec;
            for(int j = i + 1; j < flagi.size(); j++){
                vec.push_back(flagi[j]);
            }
            anagrams(name, vec);
            break;
        }
        else if(strcmp(flagi[i].c_str(), "-p") == 0 || strcmp(flagi[i].c_str(), "--palindromes") == 0){
            std::vector<std::string> vec;
            for(int j = i + 1; j < flagi.size(); j++){
                vec.push_back(flagi[j]);
            }
            palindromes(name, vec);
            break;
        }
        else if(strcmp(flagi[i].c_str(), "-o") == 0 || strcmp(flagi[i].c_str(), "--output") == 0){
            if(i+1 < flagi.size()){
                output_file = flagi[i+1];
            }else{
                output << "Brakuje sciezki do pliku by zapisac wyniki";
            }
        }
    }
    if(output_file.size() == 0){
        std::cout << output.str();
    }else{
        std::ofstream plik;
        plik.open(output_file);
        plik << output.str();
    }

    return 0;
}