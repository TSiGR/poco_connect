
#include "task1.h"
#include "transmit.h"

std::string Task::solution_1()
{
    o_str.str("");
    o_str.clear();
    int b_size = 0;
    int a[10] = {1, 6, 9, 18, 27, 36, 51, 68, 82, 101};
    int b[10];
    for (int i = 0; i < 10; ++i)
    {
        if (a[i] % 2 == 0)
        {
            b[b_size] = a[i];
            b_size++;
        }
    }
    for (int i = 0; i < b_size; ++i)
        o_str << b[i] << " ";
    o_str << "\n";
    return o_str.str();
}

std::string Task::solution_2(Poco::Net::StreamSocket& str_sock)
{
    o_str.str("");
    o_str.clear();

    std::vector<int> looks;
    std::vector<int> checks;
    std::vector<int> res;

    std::ifstream look("../../../sol_2/simple.txt");
    std::ifstream check("../../../sol_2/happy.txt");

    if (!look.is_open() || !check.is_open())
    {
        o_str << "Can't open files for reading\n";
        return o_str.str();
    }
    make_converse(look, looks);
    make_converse(check, checks);
    
    for (auto& item : looks)
    {
        if (std::binary_search(checks.begin(), checks.end(), item))
        {
            res.push_back(item);
        }
    }

    o_str << "%Ready to get files.\n";
    Transmit::transmit(getf_user, sizeof(getf_user), o_str, str_sock);

    delete_converse(look, res);
    Transmit::transmit(getf_user, sizeof(getf_user), o_str, str_sock);

    delete_converse(check, res);
    Transmit::transmit(getf_user, sizeof(getf_user), o_str, str_sock);

    look.close();
    check.close();

    o_str << "%End of file transmission.\n";
    return o_str.str();
}

std::string Task::solution_3(Poco::Net::StreamSocket& str_sock)
{
    o_str.str("");
    o_str.clear();

    std::vector<std::string> words = {"favourite", "interesting", "disarmement", "implementaion", "recognize", "substitute",
                                      "production", "neighbourhood", "wonderful", "generation", "trustment", "stronghold",
                                      "creature", "investment", "cucumber", "mushroom", "revolution", "workstation", 
                                      "elevator", "refridgerator", "forgiveness", "encouragement", "translation", "exhibition",
                                      "language", "reconstruction", "calculation", "development", "environment", "destination",
                                      "corporation", "significant", "considerable", "comfortable", "invisible", "unchecked",
                                      "emplacement", "government", "telephone", "container", "distribution"};
    srand(static_cast<unsigned int>(time(0)));
    int chos_number = rand();
    chos_number = get_randomnumber(0, words.size() - 1);
    std::string result;
    o_str << "Let's play the Hang-Man game. The word has been chosen\n";
    std::vector<char> chos_word(words[chos_number].size(), '_');
    o_str << "The word: ";
    for (auto& item : chos_word)
    {
        o_str << item << " ";
    }
    o_str << "\n";
    o_str << "Guess the letter: ";
    answer = Transmit::transmit(getf_user, sizeof(getf_user), o_str, str_sock);
    int attempts = 6;
    while (true)
    {
        char chos_letter;
        bool count_right = 0;
        bool count_miss = 0;
        while ((answer && (static_cast<int>(getf_user[0]) > 122 || 
            static_cast<int>(getf_user[0]) < 97)) || getf_user[1] != '\0')
        {
            o_str << "Input a letter in low case: ";
            answer = Transmit::transmit(getf_user, sizeof(getf_user), o_str, str_sock);
        }
        chos_letter = getf_user[0];
        auto iter = chos_word.begin();
        for (auto& item : words[chos_number])
        { 
            if (chos_letter == item && *iter == '_')
            {
                *iter = chos_letter;
                count_right = true;
                break;
            }
            else if (chos_letter == *iter && 
                    words[chos_number].find(chos_letter, std::distance(chos_word.begin(), iter) + 1) == std::string::npos)
            {
                o_str << "You have fill in all the gaps with this letter\n";
                count_miss = true;
                break;
            }
            else
            {
                iter++;
            }
        }
        if (count_right)
        {
            if (check_fill(chos_word))
            {
                o_str << "Congratulations. You win.\n";
                o_str << "The guessed word: ";
                for (auto& item : chos_word)
                    o_str << item << " ";
                o_str << '\n';
                return o_str.str();
            }
            else
            {
                o_str << "That's right: ";
                for (auto& item : chos_word)
                    o_str << item << " ";
                o_str << '\n';    
            }
        }
        else if (!count_right && !count_miss)
        {
            --attempts;
            o_str << "Incorrectly! Such a letter is absent in the word. " <<
                      "You have left " << attempts << " attempts to point out the wrong letter.\n";
        }
        if (attempts != 0)
        {
            o_str << "Guess the next letter: ";
            answer = Transmit::transmit(getf_user, sizeof(getf_user), o_str, str_sock);
        }
        else
        {
            o_str << "You have lost. Try again. The right word was " << words[chos_number] << ".\n";
            return o_str.str();
        }
    }
}

void Task::make_converse(std::ifstream& content, std::vector<int>& number)
{
    std::string conv;
    while (content >> conv)
    {
        int item;
        std::istringstream(conv) >> item;
        number.push_back(item);
    }
    content.clear();
    content.seekg(0, std::ios::beg);
}

void Task::delete_converse(std::ifstream& content, std::vector<int>& number)
{
    std::string conv;
    auto iter = number.begin();
    while (content >> conv)
    {
        int item;
        std::istringstream(conv) >> item;
        if (iter != number.end())
        {
            if (item != *iter)
            {
                o_str << item;
                o_str << '\n';
            }
            else
            {
                iter++;
            }
        }
        else
        {
            o_str << item;
            o_str << '\n';
        }
    }
}

int Task::get_randomnumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

bool Task::check_fill(std::vector<char>& fill_word)
{
    for (auto& item : fill_word)
    {
        if (item == '_')
            return false;
    }
    return true;
}