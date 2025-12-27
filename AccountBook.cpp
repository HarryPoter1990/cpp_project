#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>
#include <iomanip>
#include <limits>
#include <ios>
#include <Windows.h>
using namespace std;

struct Transaction{
    double amount;
    string type;
    string category;
    string date;
    string description;
    Transaction() : amount(0.0), type(""), category(""), date(""), description("") {}
};

struct User{
    string user_id;
    string username;
    string password;
    vector<Transaction> transactions;
    User() : user_id(""), username(""), password("") {}
};

string generate_user_id(){
    srand(static_cast<unsigned int>(time(0)));
    return to_string(time(0)) + "_" + to_string(rand() % 10000);
}

bool is_valid_date(const string& date_str){
    if(date_str.length() != 10 || date_str[4] != '-' || date_str[7] != '-'){
        return false;
    }
    for(int i = 0; i < 10; i++){
        if(i == 4 || i == 7) continue;
        if(!isdigit(static_cast<unsigned char>(date_str[i])))
            return false;
    }
    int year, month, day;
    try{
        year = stoi(date_str.substr(0, 4));
        month = stoi(date_str.substr(5, 2));
        day = stoi(date_str.substr(8, 2));
    }
    catch(...){
        return false;
    }
    if(year < 1900 || year > 2100) return false;
    if(month < 1 || month > 12) return false;
    if(day < 1 || day > 31) return false;
    if(month == 2){
        bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if(day > (is_leap ? 29 : 28)) return false;
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11){
        if(day > 30) return false;
    }
    return true;
}

bool is_valid_amount(double amount){
    return amount > 0;
}

double get_valid_double_input(const string& prompt){
    double value;
    string input;
    while(true){
        cout << prompt;
        getline(cin, input);
        try{
            input.erase(0, input.find_first_not_of(" "));
            input.erase(input.find_last_not_of(" ") + 1);
            if(input.empty()){
                cout << "输入不能为空，请重新输入!" << endl;
                continue;
            }
            value = stod(input);
            if(!is_valid_amount(value)){
                cout << "错误: 金额必须大于0!" << endl;
                continue;
            }
            return value;
        }
        catch(const invalid_argument){
            cout << "错误: 请输入有效的数字!" << endl;
        }
        catch(const out_of_range){
            cout << "错误: 数字太大或太小!" << endl;
        }
    }
}
string get_valid_string_input(const string& prompt, bool allow_empty = false){
    string input;
    while(true){
        cout << prompt;
        getline(cin, input);
        input.erase(0, input.find_first_not_of(" "));
        input.erase(input.find_last_not_of(" \t\r\n") + 1);
        if(!allow_empty && input.empty()){
            cout << "输入不能为空，请重新输入!" << endl;
            continue;
        }
        return input;
    }
}
void load_users(vector<User>& users){
    ifstream file("users.csv");
    if(!file.is_open()){
        cout << "用户文件不存在，将创建新文件。" << endl;
        return;
    }
    string line;
    while(getline(file, line)){
        if (line.empty()) continue;
        istringstream iss(line);
        User user;
        string temp;
        if(getline(iss, user.user_id, ',') &&
            getline(iss, user.username, ',') &&
            getline(iss, user.password, ',')){
            users.push_back(user);
        }
    }
    file.close();
    cout << "成功加载 " << users.size() << " 个用户。" << endl;
}
void save_users(const vector<User>& users){
    ofstream file("users.csv");
    if(!file.is_open()){
        cerr << "无法打开用户文件进行保存!" << endl;
        return;
    }
    for(const User& user : users){
        file << user.user_id << "," << user.username << "," << user.password << endl;
    }
    file.close();
    cout << "用户数据已保存。" << endl;
}
void load_transactions(User& user){
    string filename = "transactions_" + user.user_id + ".csv";
    ifstream file(filename);
    if(!file.is_open()){
        cout << "用户交易文件不存在，将创建新文件。" << endl;
        return;
    }
    string line;
    while(getline(file, line)){
        if(line.empty()) continue;
        istringstream iss(line);
        Transaction trans;
        string amount_str;
        if(getline(iss, amount_str, ',') &&
            getline(iss, trans.type, ',') &&
            getline(iss, trans.category, ',') &&
            getline(iss, trans.date, ',') &&
            getline(iss, trans.description)){
            try{
                trans.amount = stod(amount_str);
                user.transactions.push_back(trans);
            }
            catch(...){
                cerr << "无效的金额格式: " << amount_str << endl;
            }
        }
    }
    file.close();
    cout << "成功加载 " << user.transactions.size() << " 条交易记录。" << endl;
}

void save_transactions(const User& user){
    string filename = "transactions_" + user.user_id + ".csv";
    ofstream file(filename);
    if(!file.is_open()){
        cerr << "无法打开交易文件进行保存!" << endl;
        return;
    }
    for(const Transaction& trans : user.transactions){
        file << fixed << setprecision(2) << trans.amount << ","
            << trans.type << ","
            << trans.category << ","
            << trans.date << ","
            << trans.description << endl;
    }
    file.close();
    cout << "交易记录已保存。" << endl;
}

void register_user(vector<User>& users){
    User new_user;
    cout << "=== 用户注册 ===" << endl;
    new_user.username = get_valid_string_input("请输入用户名: ");
    for(const User& u : users){
        if(u.username == new_user.username){
            cout << "错误: 用户名已存在!" << endl;
            return;
        }
    }
    new_user.password = get_valid_string_input("请输入密码: ");
    new_user.user_id = generate_user_id();
    users.push_back(new_user);
    save_users(users);
    cout << "注册成功! 用户ID: " << new_user.user_id << endl;
}

User* login_user(vector<User>& users){
    string username, password;
    cout << "=== 用户登录 ===" << endl;
    username = get_valid_string_input("请输入用户名: ");
    password = get_valid_string_input("请输入密码: ");
    for(User& user : users){
        if(user.username == username && user.password == password){
            load_transactions(user);
            cout << "登录成功！欢迎, " << username << endl;
            return &user;
        }
    }
    cout << "登录失败: 用户名或密码错误!" << endl;
    return nullptr;
}

void add_transaction(User& user){
    Transaction new_trans;
    cout << "=== 添加新记录 ===" << endl;
    new_trans.amount = get_valid_double_input("请输入金额: ");
    while(true){
        new_trans.type = get_valid_string_input("请输入类型 (收入/支出): ");
        if(new_trans.type == "收入" || new_trans.type == "支出")
            break;
        cout << "错误: 类型必须是'收入'或'支出'!" << endl;
    }
    new_trans.category = get_valid_string_input("请输入类别 (例如: 餐饮, 购物, 工资): ");
    while(true){
        new_trans.date = get_valid_string_input("请输入日期 (格式: YYYY-MM-DD): ");
        if(is_valid_date(new_trans.date))
            break;
        cout << "错误: 日期格式不正确! 请使用 YYYY-MM-DD 格式。" << endl;
    }
    new_trans.description = get_valid_string_input("请输入备注: ", true);
    user.transactions.push_back(new_trans);
    save_transactions(user);
    cout << "交易记录添加成功!" << endl;
}

void view_all_transactions(const User& user){
    if(user.transactions.empty()){
        cout << "没有交易记录。" << endl;
        return;
    }
    cout << "\n=== 所有交易记录 ===" << endl;
    cout << setw(10) << "金额" << setw(8) << "类型" << setw(10) << "类别"
         << setw(12) << "日期" << setw(20) << "备注" << endl;
    cout << string(65, '-') << endl;
    for(const Transaction& trans : user.transactions){
        cout << fixed << setprecision(2) << setw(10) << trans.amount;
        cout << setw(8) << trans.type;
        cout << setw(10) << trans.category;
        cout << setw(12) << trans.date;
        string desc = trans.description;//处理长备注
        if(desc.length() > 18)
            desc = desc.substr(0, 17) + "...";
        cout << setw(20) << desc << endl;
    }
}

double calculate_balance(const User& user){
    double balance = 0.0;
    for(const Transaction& trans : user.transactions){
        if(trans.type == "收入")
            balance += trans.amount;
        else if(trans.type == "支出")
            balance -= trans.amount;
    }
    return balance;
}

void categorize_expenses(const User& user){
    map<string, double> category_totals;
    map<string, int> category_counts;
    for(const Transaction& trans : user.transactions){
        if(trans.type == "支出"){
            category_totals[trans.category] += trans.amount;
            category_counts[trans.category]++;
        }
    }
    if(category_totals.empty()){
        cout << "没有支出记录。" << endl;
        return;
    }
    cout << "\n=== 按类别统计支出 ===" << endl;
    cout << setw(15) << "类别" << setw(15) << "总金额" << setw(10) << "记录数" << endl;
    cout << string(45, '-') << endl;
    for(const auto& entry : category_totals){
        cout << setw(15) << entry.first
             << setw(15) << fixed << setprecision(2) << entry.second
             << setw(10) << category_counts[entry.first] << endl;
    }
}

void statistics(const User& user){
    cout << "\n=== 账户统计 ===" << endl;
    cout << "总余额: " << fixed << setprecision(2) << calculate_balance(user) << " 元" << endl;
    categorize_expenses(user);
}

void main_menu(){
    cout << "\n=== 个人记账系统 ===" << endl;
    cout << "1. 注册新用户" << endl;
    cout << "2. 用户登录" << endl;
    cout << "3. 退出系统" << endl;
    cout << "请选择操作 (1-3): ";
}

void user_menu(){
    cout << "\n=== 用户功能菜单 ===" << endl;
    cout << "1. 添加交易记录" << endl;
    cout << "2. 查看所有记录" << endl;
    cout << "3. 查看统计信息" << endl;
    cout << "4. 退出登录" << endl;
    cout << "请选择操作 (1-4): ";
}

int get_valid_menu_choice(int min, int max){
    int choice;
    string input;
    while(true){
        getline(cin, input);
        input.erase(0, input.find_first_not_of(" "));
        input.erase(input.find_last_not_of(" \t\r\n") + 1);
        if(input.empty()){
            cout << "输入不能为空，请重新输入!" << endl;
            continue;
        }
        try{
            choice = stoi(input);
            if(choice >= min && choice <= max){
                return choice;
            }
            cout << "错误: 请选择 " << min << "-" << max << " 之间的数字!" << endl;
        }
        catch(const invalid_argument){
            cout << "错误: 请输入有效的数字!" << endl;
        }
        catch(const out_of_range){
            cout << "错误: 数字太大或太小!" << endl;
        }
    }
}

int main(){
	//window api解决中文乱码问题
    SetConsoleOutputCP(936);
    SetConsoleCP(936);
    vector<User> all_users;
    User* current_user = nullptr;
    load_users(all_users);
    cout << "欢迎使用简易个人记账系统!" << endl;
    while(true){
        if(current_user == nullptr){
            main_menu();
            int choice = get_valid_menu_choice(1, 3);
            switch(choice){
            case 1:
                register_user(all_users);
                break;
            case 2:
                current_user = login_user(all_users);
                break;
            case 3:
                save_users(all_users);
                cout << "系统已退出" << endl;
                return 0;
            }
        }
        else{
            user_menu();
            int choice = get_valid_menu_choice(1, 4);
            switch (choice){
            case 1:
                add_transaction(*current_user);
                break;
            case 2:
                view_all_transactions(*current_user);
                break;
            case 3:
                statistics(*current_user);
                break;
            case 4:
                save_transactions(*current_user);
                cout << "已退出登录。" << endl;
                current_user = nullptr;
                break;
            }
        }
    }
    return 0;
}