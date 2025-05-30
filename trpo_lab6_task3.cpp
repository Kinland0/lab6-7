#include <iostream>
#include <string>

using namespace std;


class PostCard {
public:
    virtual void display() const = 0;
    virtual ~PostCard() = default;
};

class Present {
public:
    virtual void show() const = 0;
    virtual ~Present() = default;
};

class Cake {
public:
    virtual void describe() const = 0;
    virtual ~Cake() = default;
};


class NYCard : public PostCard {
public:
    void display() const override { cout << "Íîâîăîäí˙˙ îňęđűňęŕ\n"; }
};

class NYPresent : public Present {
public:
    void show() const override { cout << "Íîâîăîäíčé ďîäŕđîę\n"; }
};

class NYCake : public Cake {
public:
    void describe() const override { cout << "Íîâîăîäíčé ňîđň\n"; }
};

// Ęîíęđĺňíűĺ ďđîäóęňű äë˙ Äí˙ Đîćäĺíč˙
class BDCard : public PostCard {
public:
    void display() const override { cout << "Îňęđűňęŕ íŕ ÄĐ\n"; }
};

class BDPresent : public Present {
public:
    void show() const override { cout << "Ďîäŕđîę íŕ ÄĐ\n"; }
};

class BDCake : public Cake {
public:
    void describe() const override { cout << "Ňîđň íŕ ÄĐ\n"; }
};

// Ęîíęđĺňíűĺ ďđîäóęňű äë˙ 8 Ěŕđňŕ 
class March8Card : public PostCard {
public:
    void display() const override { cout << "Îňęđűňęŕ ę 8 Ěŕđňŕ\n"; }
};

class March8Present : public Present {
public:
    void show() const override { cout << "Ďîäŕđîę íŕ 8 Ěŕđňŕ\n"; }
};

class March8FlowerArrangement : public Cake { 
public:
    void describe() const override { cout << "Áóęĺň öâĺňîâ ę 8 Ěŕđňŕ\n"; }
};


class AbstractFactory {
public:
    virtual PostCard* createPostCard() const = 0;
    virtual Present* createPresent() const = 0;
    virtual Cake* createCake() const = 0;
    virtual ~AbstractFactory() = default;
};

