#include <bits/stdc++.h>

int V_COUNT = 0;


unsigned long long bin2Dec(std::string str) {
    unsigned long long number = std::stoull(str, 0, 2);
    return number;
}


long long binaryToDecimal(std::string str)
{   
    unsigned long long num;
    size_t pos = str.find('1');
    if (pos == std::string::npos) {
        return 0;
    } else if (pos > 0) {
        std::string temp = str.substr(pos);
        num = std::stoull(temp);
    } else {
        num = std::stoull(str);
    }
    
    long dec_value = 0;
    int base = 1;
    unsigned long long tmp = num;
    while(tmp) {
        long long last_digit = tmp % 10;
        tmp = tmp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}

void toBinary(std::string in, std::map<char, std::string> hex2bin, std::string &out)
{
    for (auto c: in) {
        out += hex2bin[c];
    }
}

std::pair<unsigned long long, int> parse(std::string &packet, int pos) {
    std::pair<unsigned long long, int> result;
    if (pos >= packet.size()) {
        return result;
    }
    unsigned long long version;
    unsigned long long typeID;
    std::string versionString = packet.substr(pos,3);
    pos += 3;
    std::string typeString = packet.substr(pos,3);
    version = bin2Dec(versionString);
    V_COUNT += version;
    typeID = bin2Dec(typeString);
    pos += 3;
    //std::cout << "Version count -> " << V_COUNT << std::endl;

    if (typeID != 4) {
        char lengthTypeID = packet[pos];
        pos += 1;
        std::vector<unsigned long long> values;
        if (lengthTypeID == '0') {
            // next 15 bits -> total length in bits
            std::string total_length = packet.substr(pos, 15);
            pos += 15;
            unsigned long long totalLength = bin2Dec(total_length);
            
            int start = pos; 
            while (true) {
                result = parse(packet, pos);
                values.push_back(result.first);
                int next_pos = result.second;
                assert (next_pos > pos);
                pos = next_pos;
                //std::cout << "pos=" << pos << " start=" << start << " totallength=" << totalLength << std::endl;
                if ((next_pos - start) == totalLength)
                    break;
            }
        } else {
            // next 11 bits -> number of sub-packets immediately contained by this packet
            std::string num_packets = packet.substr(pos, 11);
            unsigned long long numPackets = bin2Dec(num_packets);
            pos += 11;
            for (int i = 0; i < numPackets; i++) {
                result = parse(packet, pos);
                values.push_back(result.first);
                assert (result.second > pos);
                pos = result.second;
            }
        }
        if (typeID == 0) {
            int sum = std::accumulate(values.begin(), values.end(), 0);
            result = std::make_pair(sum, pos);
            return result;
        } else if (typeID == 1) {
            int mul = 1;
            for (auto el: values) {
                mul *= el;
            }
            result = std::make_pair(mul, pos);
            return result;
        } else if (typeID == 2) {
            auto min = std::min_element(values.begin(), values.end());
            result = std::make_pair((*min), pos);
            return result;
        } else if (typeID == 3) {
            auto max = std::max_element(values.begin(), values.end());
            result = std::make_pair((*max), pos);
            return result;
        } else if (typeID == 5) {
            if (values[0] > values[1]) {
                result = std::make_pair(1, pos);
            } else {
                result = std::make_pair(0, pos);
            }
            return result;
        } else if (typeID == 6) {
            if (values[0] < values[1]) {
                result = std::make_pair(1, pos);
            } else {
                result = std::make_pair(0, pos);
            }
            return result;
        } else if (typeID == 7) {
            if (values[0] == values[1]) {
                result = std::make_pair(1, pos);
            } else {
                result = std::make_pair(0, pos);
            }
            return result;
        }

    } else {
        int step = 5;
        std::string wholeNumber;
        while (true) {
            std::string number;
            std::string tmp = packet.substr(pos, step);
            pos += step;
            for (int j = 1; j < tmp.size(); j++) {
                number.push_back(tmp[j]);
            }
            wholeNumber += number;
            if (tmp[0] == '0') {;
                unsigned long long res = bin2Dec(wholeNumber);
                std::cout << res << std::endl;
                assert (res > 0);
                result = std::make_pair(res, pos);
                return result;
            }
        }
        
    }
    return result;
}


int main() {
    std::map<char, std::string> hexToBinary {
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'A', "1010"},
        {'B', "1011"},
        {'C', "1100"},
        {'D', "1101"},
        {'E', "1110"},
        {'F', "1111"}
    };

    std::ifstream infile ("../inputs/day16.txt");
    std::string line;
    std::getline(infile, line);
    std::cout << "Hex: " << line << std::endl;
    std::string bin;
    toBinary(line, hexToBinary, bin);
    std::cout << "Binary: " << bin << std::endl;

    std::pair<unsigned long long, int> result = parse(bin, 0);

    std::cout << V_COUNT << std::endl;
    std::cout << result.first << std::endl;

    return 0;
}