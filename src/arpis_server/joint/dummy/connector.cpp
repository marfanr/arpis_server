#include "arpis_server/joint/dummy.hpp"

namespace arpis_server {

Dummy::Dummy() {}

void Dummy::load_data() {
    for (int i = 0; i < 1000; i++)
    {
        for (int x = 0; x < 20; x++)
        {
            this->dummy_item_[i][x].id = x;
            this->dummy_item_[i][x].position = 2048;
        }
    }
    this->dummy_item_[0][0] = {id : 1, position : 2069};
    this->dummy_item_[0][1] = {id : 2, position : 2780};
    this->dummy_item_[0][2] = {id : 1, position : 2100};
    this->dummy_item_[0][3] = {id : 2, position : 2670};
    this->dummy_item_[0][4] = {id : 1, position : 2300};
    this->dummy_item_[0][5] = {id : 2, position : 2000};
    this->dummy_item_[0][6] = {id : 1, position : 1080};
    this->dummy_item_[0][7] = {id : 2, position : 2090};
    this->dummy_item_[0][8] = {id : 1, position : 2090};
    this->dummy_item_[0][9] = {id : 2, position : 2090};
    this->dummy_item_[0][10] = {id : 1, position : 2090};
    this->dummy_item_[0][11] = {id : 2, position : 2090};
    this->dummy_item_[0][12] = {id : 1, position : 2100};
    this->dummy_item_[0][13] = {id : 2, position : 2700};
    this->dummy_item_[0][14] = {id : 1, position : 2100};
    this->dummy_item_[0][15] = {id : 2, position : 2100};
    this->dummy_item_[0][16] = {id : 1, position : 2500};
    this->dummy_item_[0][17] = {id : 2, position : 2300};
    this->dummy_item_[0][18] = {id : 2, position : 2500};
    this->dummy_item_[0][19] = {id : 2, position : 2700};
    this->dummy_item_[1][0] = {id : 6, position : 2000};
    this->dummy_item_[1][1] = {id : 6, position : 2090};
    this->dummy_item_[1][2] = {id : 6, position : 2090};
    this->dummy_item_[1][3] = {id : 6, position : 2100};
    this->dummy_item_[1][4] = {id : 6, position : 2700};
    this->dummy_item_[1][5] = {id : 6, position : 2100};
    this->dummy_item_[1][6] = {id : 6, position : 2100};
    this->dummy_item_[1][7] = {id : 6, position : 2500};
    this->dummy_item_[1][8] = {id : 6, position : 2300};
    this->dummy_item_[1][9] = {id : 6, position : 2500};
    this->dummy_item_[1][10] = {id : 19, position : 2700};
    this->dummy_item_[1][11] = {id : 19, position : 2700};
    this->dummy_item_[1][12] = {id : 18, position : 2100};
    this->dummy_item_[1][13] = {id : 18, position : 2100};
    this->dummy_item_[1][14] = {id : 18, position : 2500};
    this->dummy_item_[1][15] = {id : 19, position : 2300};
    this->dummy_item_[1][16] = {id : 19, position : 2500};
    this->dummy_item_[1][17] = {id : 20, position : 2700};
    this->dummy_item_[1][18] = {id : 20, position : 2700};
}

Dummy::~Dummy() {}

}