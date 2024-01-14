#pragma once

class Location {
private:
    int x, y;

public:
    void setLocation(int x, int y);
    void getLocation(int& x, int& y) const;
};
