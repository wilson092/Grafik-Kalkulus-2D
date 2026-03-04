#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;
struct Parser {
    string src; size_t pos;
    double parseExpr(double x) {
        double res = parseTerm(x);
        while (pos < src.size() && (src[pos] == '+' || src[pos] == '-')) {
            char op = src[pos++]; double rhs = parseTerm(x);
            if (op == '+') res += rhs; else res -= rhs;
        }
        return res;
    }
    double parseTerm(double x) {
        double res = parseFactor(x);
        while (pos < src.size() && (src[pos] == '*' || src[pos] == '/')) {
            char op = src[pos++]; double rhs = parseFactor(x);
            if (op == '*') res *= rhs; else res /= rhs;
        }
        return res;
    }
    double parseFactor(double x) {
        double res = parseBase(x);
        if (pos < src.size() && src[pos] == '^') { pos++; res = pow(res, parseFactor(x)); }
        return res;
    }
    double parseBase(double x) {
        while(pos < src.size() && src[pos]==' ') pos++;
        if (pos >= src.size()) return 0;
        if (isdigit(src[pos]) || src[pos] == '.') {
            size_t end; double v = stod(src.substr(pos), &end); pos += end; return v;
        }
        if (isalpha(src[pos])) {
            string f; while(pos<src.size() && isalpha(src[pos])) f += src[pos++];
            if (f == "x") return x;
            if (src[pos] == '(') {
                pos++; double arg = parseExpr(x); if(src[pos]==')') pos++;
                if (f=="sin") return sin(arg); if (f=="cos") return cos(arg); if (f=="tan") return tan(arg);
                if (f=="sqrt") return sqrt(arg); if (f=="log") return log(arg); if (f=="exp") return exp(arg);
                if (f=="abs") return abs(arg);
            }
        }
        if (src[pos] == '(') { pos++; double v = parseExpr(x); if(src[pos]==')') pos++; return v; }
        if (src[pos] == '-') { pos++; return -parseBase(x); }
        return 0;
    }
    double solve(string s, double x) { src = s; pos = 0; try { return parseExpr(x); } catch(...) { return 0; } }
} parser;

double xMin = -10.0, xMax = 10.0;
double yMin = -6.0,  yMax = 6.0;
const int W = 1200, H = 700;

float sx(double x) { return (float)((x - xMin) / (xMax - xMin) * W); }
float sy(double y) { return (float)(H - (y - yMin) / (yMax - yMin) * H); }

string fmt(double v) {
    stringstream ss; ss << fixed << setprecision(2) << v;
    string s = ss.str();
    if(s.find('.')!=string::npos){ while(s.back()=='0') s.pop_back(); if(s.back()=='.') s.pop_back(); }
    return s;
}

int main() {
    sf::RenderWindow win(sf::VideoMode(W, H + 100), "Graph Calc - Tutup Window untuk Lihat Hasil CLI");
    win.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\ramsa\\Coding\\Kuliah\\Calculus_2D\\resources\\OpenSans-Regular.ttf")){
        if (!font.loadFromFile("OpenSans-Regular.ttf")) {
        cout << "Font gagal dimuat!" << endl;
        return 1;
    
    } 
    
}
    string strFunc = "sin(x)";
    string strXmin = "-10";
    string strXmax = "10";
   
    int activeField = 0;
    sf::FloatRect boxFunc(80, H+20, 400, 30);
    sf::FloatRect boxMin(600, H+20, 100, 30);
    sf::FloatRect boxMax(800, H+20, 100, 30);
    auto updateRange = [&]() {
        try {
            double newMin = stod(strXmin); double newMax = stod(strXmax);
            if (newMin < newMax) { xMin = newMin; xMax = newMax; }
            double rangeY = (xMax - xMin) * ((double)H/W);
            yMin = -(rangeY/2.0); yMax = (rangeY/2.0);
        } catch (...) {}
    };
    updateRange();

    while (win.isOpen()) {
        sf::Event ev;
        while (win.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) win.close();
            if (ev.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f m((float)ev.mouseButton.x, (float)ev.mouseButton.y);
                if (boxFunc.contains(m)) activeField = 0;
                else if (boxMin.contains(m)) activeField = 1;
                else if (boxMax.contains(m)) activeField = 2;
            }
            if (ev.type == sf::Event::TextEntered) {
                if (ev.text.unicode < 128) {
                    char c = (char)ev.text.unicode;
                    string* target = (activeField==0 ? &strFunc : (activeField==1 ? &strXmin : &strXmax));
                    if (c == 8) { if (!target->empty()) target->pop_back(); }
                    else if (c == 13) { updateRange(); }
                    else if (c >= 32) { *target += c; }
                }}}
        win.clear(sf::Color::White);

        double range = xMax - xMin;
        double step = pow(10, floor(log10(range))) / 2.0;
        if (range / step > 20) step *= 2;

        for (double x = floor(xMin/step)*step; x <= xMax; x += step) {
            float px = sx(x);
            if(px >=0 && px <= W) {
                win.draw(new sf::Vertex[2]{{{px, 0}, sf::Color(220,220,220)}, {{px, (float)H}, sf::Color(220,220,220)}}, 2, sf::Lines);
                sf::Text t(fmt(x), font, 12); t.setFillColor(sf::Color::Black); t.setPosition(px+2, sy(0)+2); win.draw(t);
        }}
        for (double y = floor(yMin/step)*step; y <= yMax; y += step) {
            float py = sy(y);
            if(py >=0 && py <= H) {
                win.draw(new sf::Vertex[2]{{{0, py}, sf::Color(220,220,220)}, {{(float)W, py}, sf::Color(220,220,220)}}, 2, sf::Lines);
                sf::Text t(fmt(y), font, 12); t.setFillColor(sf::Color::Black); t.setPosition(sx(0)+2, py-16); win.draw(t);
        }}
       
        sf::RectangleShape axX(sf::Vector2f(W, 2)); axX.setPosition(0, sy(0)); axX.setFillColor(sf::Color::Black); win.draw(axX);
        sf::RectangleShape axY(sf::Vector2f(2, H)); axY.setPosition(sx(0), 0); axY.setFillColor(sf::Color::Black); win.draw(axY);
        sf::VertexArray graph(sf::LineStrip);
        double dx = range / W;
        for (int i = 0; i <= W; ++i) {
            double x = xMin + i * dx;
            double y = parser.solve(strFunc, x);
            if (std::isfinite(y)) {
                float py = sy(y);
                if (py > -H && py < 2*H) graph.append(sf::Vertex(sf::Vector2f((float)i, py), sf::Color::Blue));
            } else if(graph.getVertexCount()>0) { win.draw(graph); graph.clear(); }
        }
        win.draw(graph);

        sf::RectangleShape uiBg(sf::Vector2f(W, 100)); uiBg.setPosition(0, H); uiBg.setFillColor(sf::Color(240,240,240));
        uiBg.setOutlineThickness(1); uiBg.setOutlineColor(sf::Color::Black); win.draw(uiBg);

        auto drawBox = [&](sf::FloatRect r, string s, string l, int id) {
            sf::RectangleShape box(sf::Vector2f(r.width, r.height));
            box.setPosition(r.left, r.top); box.setFillColor(sf::Color::White);
            box.setOutlineThickness(activeField==id?2:1); box.setOutlineColor(activeField==id?sf::Color::Blue:sf::Color(100,100,100));
            win.draw(box);
            sf::Text t(s, font, 18); t.setFillColor(sf::Color::Black); t.setPosition(r.left+5, r.top+2); win.draw(t);
            sf::Text lb(l, font, 14); lb.setFillColor(sf::Color::Black); lb.setPosition(r.left, r.top-20); win.draw(lb);
        };
        drawBox(boxFunc, strFunc, "f(x) =", 0);
        drawBox(boxMin, strXmin, "X Min", 1);
        drawBox(boxMax, strXmax, "X Max", 2);
        win.display();
    }

    cout << "\n\n";
    cout << "=========================================" << endl;
    cout << "      HASIL PERHITUNGAN AKHIR (CLI)      " << endl;
    cout << "=========================================" << endl;
    cout << " Fungsi : " << strFunc << endl;
    cout << " Range  : " << xMin << "  s/d  " << xMax << endl;
    cout << "-----------------------------------------" << endl;
    cout << "      x       |        f(x)      " << endl;
    cout << "-----------------------------------------" << endl;

    double stepCli = (xMax - xMin) / 20.0;
    if (stepCli <= 0.0001) stepCli = 0.1;
    for (double x = xMin; x <= xMax + (stepCli/10.0); x += stepCli) {
        double y = parser.solve(strFunc, x);
        cout << fixed << setprecision(3) << setw(10) << x << "    |  ";
        if (isfinite(y)) cout << setw(12) << y << endl;
        else cout << "     NaN     " << endl;
    }
    cout << "-----------------------------------------" << endl; cout << "Tekan Enter untuk keluar..."; cin.get();
    return 0;
}
