
#include <functional>
#include <iostream>
#include <cstring>
#include <utility>

class String{
    private:
        char* data;
        size_t length;
    public:
        String():data(nullptr),length(0){}
        String(const char* str){
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        }
        //copy constructor
        String(const String& other){
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        //move constructor
        String(String&& other) noexcept{
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        ~String(){
            delete[] data;
        }
        String& operator=(const String& other){
            if(this != &other){
                String tmp(other);
                swap(*this, tmp);
            }
            return *this;
        }
        String& operator=(String&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                length = other.length;
                other.data = nullptr;
                other.length = 0;
            }
            return *this;
        }
        friend void swap(String& first, String& second) {
                using std::swap;
                swap(first.data, second.data);
                swap(first.length, second.length);
            }
            String operator+(const String& other) const {
            String result;
            result.length = length + other.length;
            result.data = new char[result.length + 1];
            strcpy(result.data, data);
            strcat(result.data, other.data);
            return result;
        }

        // Overloaded == operator for comparison
        bool operator==(const String& other) const {
            return (length == other.length) && (strcmp(data, other.data) == 0);
        }

        // Overloaded != operator for comparison
        bool operator!=(const String& other) const {
            return !(*this == other);
        }
        // Overloaded << operator for output
        friend std::ostream& operator<<(std::ostream& os, const String& str) {
            os << str.data;
            return os;
        }
};
int main()
{
    String s1("Hello");
    String s2("World");

    s1 = s2; // Copy assignment
    std::cout << "s1 after copy assignment: " << s1 << std::endl;

    String s3 = "Move";
    String s4 = std::move(s3); // Move constructor
    std::cout << "s4 after move construction: " << s4 << std::endl;
    std::cout << "s3 after move construction: " << s3 << std::endl; // s3 is moved-from, so it's in a valid but unspecified state

    String s5("Concatenated");
    String s6(" String");
    String s7 = s5 + s6; // Concatenation
    std::cout << "Concatenated string: " << s7 << std::endl;
}
