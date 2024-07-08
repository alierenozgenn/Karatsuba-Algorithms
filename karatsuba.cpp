#include <iostream>
#include <string>

// İki uzun sayıyı çarpan Karatsuba algoritması
std::string addStrings(const std::string &num1, const std::string &num2) {
    std::string result = "";
    int carry = 0, sum = 0;
    int i = static_cast<int>(num1.size()) - 1, j = static_cast<int>(num2.size()) - 1;

    while (i >= 0 || j >= 0 || carry) {
        sum = carry;
        if (i >= 0) sum += num1[static_cast<std::string::size_type>(i--)] - '0';
        if (j >= 0) sum += num2[static_cast<std::string::size_type>(j--)] - '0';
        carry = sum / 10;
        sum = sum % 10;
        result.insert(result.begin(), static_cast<char>(sum + '0'));
    }
    return result;
}

std::string subtractStrings(const std::string &num1, const std::string &num2) {
    std::string result = "";
    int carry = 0, diff = 0;
    int i = static_cast<int>(num1.size()) - 1, j = static_cast<int>(num2.size()) - 1;

    while (i >= 0 || j >= 0) {
        diff = (num1[static_cast<std::string::size_type>(i)] - '0') - (j >= 0 ? (num2[static_cast<std::string::size_type>(j)] - '0') : 0) - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.insert(result.begin(), static_cast<char>(diff + '0'));
        i--; j--;
    }

    // Leading zeros
    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }

    return result;
}

std::string karatsubaMultiply(const std::string &x, const std::string &y) {
    size_t n = std::max(x.size(), y.size());
    if (n == 1) return std::to_string((x[0] - '0') * (y[0] - '0'));

    size_t m = n / 2;

    std::string x1 = x.substr(0, x.size() - m);
    std::string x0 = x.substr(x.size() - m);
    std::string y1 = y.substr(0, y.size() - m);
    std::string y0 = y.substr(y.size() - m);

    std::string z2 = karatsubaMultiply(x1, y1);
    std::string z0 = karatsubaMultiply(x0, y0);
    std::string z1 = karatsubaMultiply(addStrings(x1, x0), addStrings(y1, y0));
    z1 = subtractStrings(subtractStrings(z1, z2), z0);

    for (size_t i = 0; i < 2 * m; i++) z2 += '0';
    for (size_t i = 0; i < m; i++) z1 += '0';

    return addStrings(addStrings(z2, z1), z0);
}

int main() {
    std::string num1 = "1234";
    std::string num2 = "5678";

    std::string result = karatsubaMultiply(num1, num2);

    std::cout << "Karatsuba Çarpımı: " << result << std::endl;

    return 0;
}
