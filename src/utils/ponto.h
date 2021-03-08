#ifndef ENGINE_PONTO_H
#define ENGINE_PONTO_H

class Ponto {
    private:
        float x, y, z;
    public:
        Ponto(float x, float y, float z);
        float getX();
        float getY();
        float getZ();
};

#endif //ENGINE_PONTO_H