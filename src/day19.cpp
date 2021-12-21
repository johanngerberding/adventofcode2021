#include <istream>
#include <ostream>
#include <stdexcept>
#include <array>
#include <cstdint>
#include <functional>
#include <iosfwd>
#include <optional>
#include <vector>
#include <algorithm>
#include <deque>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_set>
#include <iostream>
#include <fstream>


using Rotation = std::array<std::pair<int, int>, 3>;
inline const constexpr int X = 0;
inline const constexpr int Y = 1;
inline const constexpr int Z = 2;
inline const constexpr int POS = 1;
inline const constexpr int NEG = -1;

inline const constexpr std::array<Rotation, 24> ROTATIONS({
        {{{X, POS}, {Y, POS}, {Z, POS}}}, 
        {{{X, POS}, {Z, POS}, {Y, NEG}}},
        {{{X, POS}, {Y, NEG}, {Z, NEG}}},
        {{{X, POS}, {Z, NEG}, {Y, POS}}},
        {{{X, NEG}, {Y, POS}, {Z, NEG}}},
        {{{X, NEG}, {Z, NEG}, {Y, NEG}}},
        {{{X, NEG}, {Y, NEG}, {Z, POS}}},
        {{{X, NEG}, {Z, POS}, {Y, POS}}},
        {{{Y, POS}, {X, POS}, {Z, NEG}}},
        {{{Y, POS}, {Z, NEG}, {X, NEG}}},
        {{{Y, POS}, {X, NEG}, {Z, POS}}},
        {{{Y, POS}, {Z, POS}, {X, POS}}},
        {{{Y, NEG}, {X, POS}, {Z, POS}}},
        {{{Y, NEG}, {Z, POS}, {X, NEG}}},
        {{{Y, NEG}, {X, NEG}, {Z, NEG}}},
        {{{Y, NEG}, {Z, NEG}, {X, POS}}},
        {{{Z, POS}, {X, POS}, {Y, POS}}},
        {{{Z, POS}, {Y, POS}, {X, NEG}}},
        {{{Z, POS}, {X, NEG}, {Y, NEG}}},
        {{{Z, POS}, {Y, NEG}, {X, POS}}},
        {{{Z, NEG}, {X, POS}, {Y, NEG}}},
        {{{Z, NEG}, {Y, NEG}, {X, NEG}}},
        {{{Z, NEG}, {X, NEG}, {Y, POS}}},
        {{{Z, NEG}, {Y, POS}, {X, POS}}},
});

struct Point3D {
    int64_t x;
    int64_t y;
    int64_t z;

    Point3D rotate(const Rotation &) const;
    int64_t manhattan() { return std::abs(x) + std::abs(y) + std::abs(z); }

    friend std::istream &operator>>(std::istream &, Point3D &);
    friend std::ostream &operator<<(std::ostream &, Point3D &);

    friend Point3D operator-(const Point3D &, const Point3D &);
    friend Point3D operator+(const Point3D &, const Point3D &);

    friend auto operator<=>(const Point3D &, const Point3D &) = default;
};



template <> struct std::hash<Point3D> {
    std::size_t operator()(Point3D const &s) const noexcept {
        std::size_t h1 = std::hash<int64_t>{}(s.x);
        std::size_t h2 = std::hash<int64_t>{}(s.y);
        std::size_t h3 = std::hash<int64_t>{}(s.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};


std::istream &operator>>(std::istream &s, Point3D &b) {
    char delim;
    int coord;

    if (!(s >> coord))
        return s;

    b.x = coord;

    if (!(s >> delim) || delim != ',')
        throw std::runtime_error("Found unexpected delimiter.");

    if (!(s >> b.y >> delim >> b.z) || delim != ',')
        throw std::runtime_error("Failed to parse y and z coordinates.");

    return s;
}

std::ostream &operator<<(std::ostream &o, const Point3D &b) {
    o << b.x << "," << b.y << "," << b.z;
    return o;
}

Point3D Point3D::rotate(const Rotation &rot) const {
    const int64_t *vals[3] = {&x, &y, &z};
    return {
        (*vals[rot[0].first]) * rot[0].second,
        (*vals[rot[1].first]) * rot[1].second,
        (*vals[rot[2].first]) * rot[2].second
    };
}

Point3D operator-(const Point3D &lhs, const Point3D &rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

Point3D operator+(const Point3D &lhs, const Point3D &rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

using Beacon = Point3D;

struct ScannerOrientation {
    Rotation rotation;
    Point3D position;
};

struct Scanner {
    int64_t scanner_id;
    std::vector<Beacon> beacons;
    Point3D position;

    std::optional<ScannerOrientation> overlaps(const Scanner &other, uint64_t threshold) const;
    void normalize(const ScannerOrientation &);

    friend std::istream &operator>>(std::istream &, Scanner &);
    friend std::ostream &operator<<(std::ostream &, Scanner &);
};


void normalize_scanners(std::vector<Scanner> &scanners, uint64_t threshold);

std::istream &operator>>(std::istream &s, Scanner &scan) {
    std::string line;
    std::string_view header = "--- scanner ";
    std::stringstream parse;
    scan.beacons.clear();

    while(getline(s, line)) {
        if (line == "") {
            break;
        }
        if (line.starts_with(header)) {
            scan.scanner_id = std::stoll(line.substr(header.length()));
            continue;
        }
        parse.clear();
        parse.str(line);
        Beacon b;
        if (parse >> b) {
            scan.beacons.push_back(b);
        } else {
            return s;
        }
    }
    return s;
}

std::ostream &operator<<(std::ostream &s, const Scanner &scan) {
    s << "--- scanner " << scan.scanner_id << "---\n";
    std::ranges::copy(scan.beacons, std::ostream_iterator<Beacon>(s, "\n"));
    return s;
}

std::optional<ScannerOrientation> Scanner::overlaps(const Scanner &other, uint64_t threshold) const {
    for (auto &rotation: ROTATIONS) {
        std::unordered_map<Beacon, uint32_t> cnts;
        for (auto &lhs : beacons) {
            for (auto &rhs : other.beacons ) {
                cnts[lhs - rhs.rotate(rotation)]++;
            }
        }
    
        for (auto &el: cnts) {
            if (el.second >= threshold) {
                return ScannerOrientation{rotation, el.first};
            }
        }
    }
    return {};
}

void Scanner::normalize(const ScannerOrientation &orientation) {
    for (auto &beacon: beacons) {
        beacon = beacon.rotate(orientation.rotation) + orientation.position;
    }
    position = orientation.position;
}

void normalize_scanner(std::vector<Scanner> &scanners, uint64_t threshold) {
    std::unordered_set<int64_t> fixed;
    std::deque<int64_t> queue;
    fixed.insert(0);
    queue.push_back(0);
    scanners[0].position = Point3D{0,0,0};
    while (!queue.empty()) {
        auto tested = queue.front();
        queue.pop_front();
        for (size_t other = 0; other < scanners.size(); other++) {
            if (fixed.contains(other))
                continue;
            auto rot = scanners[tested].overlaps(scanners[other], threshold);
            if (!rot.has_value()) {
                continue;
            }
            scanners[other].normalize(rot.value());
            queue.push_back(other);
            fixed.insert(other);
        }
    }
}

int main() {
    std::ifstream input("../inputs/day19.txt");
    std::vector<Scanner> scanners;
    std::ranges::copy(std::ranges::istream_view<Scanner>(input), std::back_insert_iterator(scanners));

    if (scanners.size() != 26)
        throw std::runtime_error("Failed to read input.");

    normalize_scanners(scanners, 12);

    std::unordered_set<Beacon> unique_beacons;
    for (const auto &s : scanners) {
        for (const auto &b : s.beacons) {
            unique_beacons.insert(b);
        }
    }
    std::cout << "Detected " << unique_beacons.size() << " unique beacons.\n";

    int64_t best = 0;
    for (auto lhs : scanners) {
        for (auto rhs : scanners) {
            best = std::max(best, (lhs.position - rhs.position).manhattan());
        }
    }

    std::cout << "Biggest manhattan distance between two scanners is " << best << "\n";

}
