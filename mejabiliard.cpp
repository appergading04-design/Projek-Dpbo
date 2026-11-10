#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

using namespace sf;
using namespace std;

class mejabiliard{
private:
    RectangleShape bagianmeja_bola;
    RectangleShape bagianmeja_pinggir;
    vector<CircleShape> bagianlubang;

public:
    // Urutan parameter: posisi dulu, baru ukuran (agar sesuai dengan pemanggilan)
    mejabiliard(Vector2f position, Vector2f ukuran){
        // Setup bagian alas meja (kain hijau)
        bagianmeja_bola.setSize(ukuran);
        bagianmeja_bola.setPosition(position);
        bagianmeja_bola.setFillColor(Color::Green);
        
        // Setup bagian pinggir alas meja (dibuat lebih besar dari kain hijau)
        bagianmeja_pinggir.setFillColor(Color{70, 40, 20});
        bagianmeja_pinggir.setSize({ukuran.x + 80.f, ukuran.y + 80.f});
        bagianmeja_pinggir.setPosition({position.x - 40.f, position.y - 40.f});

        float ukuran_Lubangmeja = 25.f;

        vector<Vector2f> ukuranlubang1 = {
            {position.x, position.y},                               // Kiri atas
            {position.x + ukuran.x / 2.f, position.y - 5.f},          // Tengah atas
            {position.x + ukuran.x, position.y},                    // Kanan atas
            {position.x, position.y + ukuran.y},                    // Kiri bawah
            {position.x + ukuran.x / 2.f, position.y + ukuran.y + 5.f}, // Tengah bawah
            {position.x + ukuran.x, position.y + ukuran.y}          // Kanan bawah
        };

        for(const auto& tujuan : ukuranlubang1){
            CircleShape lubang(ukuran_Lubangmeja);
            lubang.setPosition(tujuan);
            lubang.setFillColor(Color::Black);
            lubang.setOrigin({ukuran_Lubangmeja, ukuran_Lubangmeja});
            bagianlubang.push_back(lubang);
        }
    }
    void draw(sf::RenderWindow &window) {
        window.draw(bagianmeja_pinggir);   
        window.draw(bagianmeja_bola); 

        // Gambar semua lubang meja
        for (const auto &lubang : bagianlubang) {
            window.draw(lubang);
        }
    }
};

int main(){
    RenderWindow window(VideoMode({1850, 900}), "Game Biliard");
    window.setFramerateLimit(60);

    Clock waktu;
    mejabiliard meja({350.f, 200.f}, {1150.f, 550.f});

    while (window.isOpen()){
        float waktu1 = waktu.restart().asSeconds();
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        Color backgroundwarna({0, 40, 40});
        window.clear(backgroundwarna);
        
        // Render meja dan bola sekaligus
        meja.draw(window);
        
        window.display();
    }
}