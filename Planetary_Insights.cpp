#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include<windows.h>


#define PI 3.14159265
#define ORANGE COLOR(255, 165, 0)
#define DARKBLUE COLOR(0, 0, 139)

class Planet {
public:
    int radius;
    int orbitRadius;
    float angle;
    float speed;
    int color;
    std::string name;
    std::string info;
    Planet* moon;
    bool hasRings;
   
    Planet(int r, int o, float s, int c, const std::string& n, const std::string& i, bool rings = false) 
        : radius(r), orbitRadius(o), speed(s), color(c), name(n), info(i), angle(0), moon(NULL), hasRings(rings) {}

    void setMoon(Planet* m) {
        moon = m;
    }

    void draw(int centerX, int centerY) {
        int planetX = centerX + orbitRadius * cos(angle);
        int planetY = centerY + orbitRadius * sin(angle);

        setcolor(WHITE);
        circle(centerX, centerY, orbitRadius);

        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        circle(planetX, planetY, radius);
        floodfill(planetX, planetY, color);

        if (hasRings) {
            setcolor(LIGHTGRAY);
            ellipse(planetX, planetY, 0, 360, radius + 5, radius / 2);
            ellipse(planetX, planetY, 0, 360, radius + 7, radius / 2 + 1);
        }

        setcolor(WHITE);
        outtextxy(planetX - 20, planetY - radius - 15, (char*)name.c_str());

        if (moon) {
            moon->draw(planetX, planetY);
        }
    }

    void update() {
        angle += speed;
        if (angle > 2 * PI) {
            angle -= 2 * PI;
        }
        if (moon) {
            moon->update();
        }
    }

    bool isClicked(int mouseX, int mouseY, int centerX, int centerY) {
        int planetX = centerX + orbitRadius * cos(angle);
        int planetY = centerY + orbitRadius * sin(angle);
        int dx = mouseX - planetX;
        int dy = mouseY - planetY;
        return (dx*dx + dy*dy <= radius*radius);
    }
};

class Comet {
public:
    float x, y;
    float speed;
    float angle;
    int tailLength;
    bool active;
    std::string info;

    Comet() : x(0), y(0), speed(0), angle(0), tailLength(0), active(false), info("Comets are icy bodies that release gas and dust when they get close to the Sun") {}

    void initialize(int screenWidth, int screenHeight) {
        int side = rand() % 4;
        switch(side) {
            case 0: // Top
                x = rand() % screenWidth;
                y = 0;
                angle = PI / 2 + (rand() % 90 - 45) * PI / 180;
                break;
            case 1: // Right
                x = screenWidth;
                y = rand() % screenHeight;
                angle = PI + (rand() % 90 - 45) * PI / 180;
                break;
            case 2: // Bottom
                x = rand() % screenWidth;
                y = screenHeight;
                angle = 3 * PI / 2 + (rand() % 90 - 45) * PI / 180;
                break;
            case 3: // Left
                x = 0;
                y = rand() % screenHeight;
                angle = (rand() % 90 - 45) * PI / 180;
                break;
        }
        speed = 1 + rand() % 5;
        tailLength = 30 + rand() % 70;
        active = true;
    }

    void update() {
        if (!active) return;
        x += speed * cos(angle);
        y += speed * sin(angle);
    }

    void draw() {
        if (!active) return;
        setcolor(WHITE);
        setlinestyle(SOLID_LINE, 0, 3);
        
        circle(x, y, 3);
        floodfill(x, y, WHITE);

        for (int i = 0; i < tailLength; i++) {
            int alpha = 255 - (i * 255 / tailLength);
            setcolor(COLOR(alpha, alpha, alpha));
            line(x - i*cos(angle), y - i*sin(angle), 
                 x - (i+1)*cos(angle), y - (i+1)*sin(angle));
        }
    }

    bool isOffScreen(int screenWidth, int screenHeight) {
        return x < 0 || x > screenWidth || y < 0 || y > screenHeight;
    }
};
class Asteroid {
public:
    float angle;
    float orbitRadius;
    float speed;

    Asteroid(float minRadius, float maxRadius) {
        angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * PI;
        orbitRadius = minRadius + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (maxRadius - minRadius);
        speed = 0.001f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.002f;
    }

    void update(float timeScale) {
        angle += speed * timeScale;
        if (angle > 2 * PI) {
            angle -= 2 * PI;
        }
    }


   void draw(int centerX, int centerY) const {  // Added 'const' here
        int x = centerX + orbitRadius * cos(angle);
        int y = centerY + orbitRadius * sin(angle);
        putpixel(x, y, LIGHTGRAY);
    }
};
class AsteroidBelt {
public:
    std::vector<Asteroid> asteroids;
    float minRadius;
    float maxRadius;
    std::string info;

    AsteroidBelt(int numAsteroids, float minR, float maxR) 
        : minRadius(minR), maxRadius(maxR), 
          info("The asteroid belt is a region between\nMars and Jupiter containing many\nsmall, rocky bodies called asteroids.") {
        for (int i = 0; i < numAsteroids; ++i) {
            asteroids.emplace_back(minRadius, maxRadius);
        }
    }

       void update(float timeScale) {
        for (auto& asteroid : asteroids) {
            asteroid.update(timeScale);
        }
    }

    void draw(int centerX, int centerY) const {  // Added 'const' here
        for (const auto& asteroid : asteroids) {
            asteroid.draw(centerX, centerY);
        }
    }
};

void drawStars(int numStars) {
    for (int i = 0; i < numStars; ++i) {
        int x = rand() % getmaxx();
        int y = rand() % getmaxy();
        putpixel(x, y, WHITE);
    }
}

void displayInfoBox(const std::string& info, int x, int y) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(x, y, x + 300, y + 100);
    rectangle(x, y, x + 300, y + 100);
    
    // Split the info string into multiple lines
    std::string line;
    int lineY = y + 10;
    for (char c : info) {
        if (c == '\n' || line.length() >= 40) {
            outtextxy(x + 10, lineY, (char*)line.c_str());
            lineY += 20;
            line.clear();
        }
        if (c != '\n') line += c;
    }
    if (!line.empty()) {
        outtextxy(x + 10, lineY, (char*)line.c_str());
    }
}

void displayPlanetInfo(const std::string& info) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, getmaxy() - 40, getmaxx(), getmaxy());
    setcolor(WHITE);
    outtextxy(10, getmaxy() - 30, (char*)info.c_str());
}

void displayTimeInfo(float timeScale) {
    char buffer[50];
    sprintf(buffer, "Time Scale: %.2fx", timeScale);
    setcolor(WHITE);
    outtextxy(10, 10, buffer);
}

int main() {
    int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");

    int screenWidth = getmaxx();
    int screenHeight = getmaxy();
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;
     Planet sun(30, 0, 0, YELLOW, "Sun", "The Sun is the star at the center of our solar system.\nIt provides light and heat to all the planets.");
    Planet mercury(5, 70, 0.05, LIGHTGRAY, "Mercury", "Smallest planet, closest to the Sun.\nExtreme temperatures, cratered surface.");
    Planet venus(8, 100, 0.03, ORANGE, "Venus", "Similar size to Earth, toxic atmosphere.\nHottest planet due to greenhouse effect.");
    Planet earth(10, 130, 0.02, BLUE, "Earth", "Our home planet, supports life.\nDiverse ecosystems, liquid water.");
    Planet mars(6, 160, 0.015, RED, "Mars", "Known as the Red Planet.\nHas the largest volcano in the solar system.");
    Planet jupiter(12, 210, 0.01, LIGHTRED, "Jupiter", "Largest planet, gas giant.\nHas the Great Red Spot storm.", true);
    Planet saturn(10, 260, 0.008, BROWN, "Saturn", "Known for its beautiful rings.\nLeast dense planet in the solar system.", true);
    Planet uranus(8, 310, 0.006, CYAN, "Uranus", "Ice giant, tilted on its side.\nBlue-green color due to methane.");
    Planet neptune(8, 360, 0.005, DARKBLUE, "Neptune", "Windiest planet in the solar system.\nDark spot and blue color.");

    Planet earthMoon(3, 20, 0.1, LIGHTGRAY, "Moon", "Earth's only natural satellite.\nResponsible for ocean tides.");
    Planet marsMoon(3, 25, 0.08, LIGHTGRAY, "Phobos", "One of Mars' two moons.\nOrbits very close to Mars' surface.");

    earth.setMoon(&earthMoon);
    mars.setMoon(&marsMoon);
 	AsteroidBelt asteroidBelt(1000, 185, 200);

    std::vector<Planet*> planets = {&mercury, &venus, &earth, &mars, &jupiter, &saturn, &uranus, &neptune};

    bool paused = false;
    int mouseX, mouseY;
    int page = 0;
	bool educationalMode = false;
	float timeScale =1.0f;
	
    srand(time(0));

    Comet comet;
    int cometSpawnTimer = 0;
    int cometSpawnInterval = 300;

    while (true) {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        drawStars(100);
        sun.draw(centerX, centerY);
        
        asteroidBelt.draw(centerX, centerY);
        if (!paused) {
            asteroidBelt.update(timeScale);
        }

        for (Planet* planet : planets) {
            if (!paused) planet->update();
            planet->draw(centerX, centerY);
        }

        if (!paused) {
            if (!comet.active) {
                cometSpawnTimer++;
                if (cometSpawnTimer >= cometSpawnInterval) {
                    comet.initialize(screenWidth, screenHeight);
                    cometSpawnTimer = 0;
                }
            } else {
                comet.update();
                if (comet.isOffScreen(screenWidth, screenHeight)) {
                    comet.active = false;
                }
            }
        }
        comet.draw();


   if (educationalMode) {
            if (comet.active) {
                displayInfoBox(comet.info, 10, 10);
            }
        }
        
        displayTimeInfo(timeScale);
        
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            mouseX = mousex();
            mouseY = mousey();
            for (Planet* planet : planets) {
            	if (educationalMode) {
                        displayInfoBox(planet->info, mouseX, mouseY);
                    }
                
                if (sqrt(pow(mouseX - centerX, 2) + pow(mouseY - centerY, 2)) >= asteroidBelt.minRadius &&
                sqrt(pow(mouseX - centerX, 2) + pow(mouseY - centerY, 2)) <= asteroidBelt.maxRadius) {
                displayInfoBox(asteroidBelt.info, mouseX, mouseY);
            }
                        
                if (planet->isClicked(mouseX, mouseY, centerX, centerY)) {
                    std::string info = planet->name + " - Orbit Radius: " + std::to_string(planet->orbitRadius) + 
                                       ", Speed: " + std::to_string(planet->speed);
                    displayPlanetInfo(info);
                    break;
                }
            }
        }

         if (kbhit()) {
            char key = getch();
            switch (key) {
                case 'p':
                case 'P':
                    paused = !paused;
                    break;
                case 'e':
                case 'E':
                    educationalMode = !educationalMode;
                    break;
                case '+':
                case '=':
                    timeScale = std::min(timeScale + 0.1f, 5.0f);  // Increase time scale, max 5x
                    break;
                case '-':
                case '_':
                    timeScale = std::max(timeScale - 0.1f, 0.1f);  // Decrease time scale, min 0.1x
                    break;
                case 'r':
                case 'R':
                    timeScale = 1.0f;  // Reset time scale to normal
                    break;
                case 27:  // ESC key
                    
                    return 0;
            }
        }

        page = 1 - page;
        delay(20);
    }

    
    return 0;
}
