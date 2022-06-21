#include "tiles.h"
Tiles::Tiles(){
    for(qint16 i = 9; i >= 0; i--){
        tiles.append(ATTRIBUTES(i));
    }
}

Tiles::Tiles(QVector<ATTRIBUTES> priority){
    Tiles::setTiles(priority);
}

Tiles::Tiles(QVector<QString> priority){
    for(auto & at : priority){
        for(qint16 i = 0; i < 10; i++){
            QString newWord = translateATTRIBUTES(ATTRIBUTES(i));
            if(at == newWord){
                tiles.push_back(ATTRIBUTES(i));
            }
        }
    }
}

void Tiles::dropDown(qint16 index){
    ATTRIBUTES temp = tiles[index];
    tiles.erase(tiles.begin() + index);
    tiles.push_front(temp);
}

void Tiles::setTiles(QVector<ATTRIBUTES> priority){
    for(qint16 i = 0; i < 10; i ++){
        if(tiles.size() <= i)
            tiles.append(priority[i]);
        else
            tiles[i] = priority[i];
    }
}

void Tiles::moveTile(qint16 source, qint16 destination){
    ATTRIBUTES temp = tiles[source];
    tiles.erase(tiles.begin() + source);
    tiles.emplace(tiles.begin() + destination, temp);
}

void Tiles::shuffleTiles(QVector<qint16> chances){

    // Create a random device and use it to generate a random seed
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();

    // Initialize a default_random_engine with the seed
    std::default_random_engine myRandomEngine(seed);

    // Initialize a uniform_int_distribution to produce values between 0 and 100
    std::uniform_int_distribution<int> myUnifIntDist(0, 100);

    for(qint16 i = 9; i >= 0; i--){
        qint16 random = myUnifIntDist(myRandomEngine);
        if(random <= chances[i])
            Tiles::dropDown(i);
    }
}
