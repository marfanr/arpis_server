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
    this->dummy_item_[0][0] = {id : 1, position : 2248};
    this->dummy_item_[0][1] = {id : 2, position : 2048};
    this->dummy_item_[0][2] = {id : 3, position : 2048};
    this->dummy_item_[0][3] = {id : 4, position : 2048};
    this->dummy_item_[0][4] = {id : 5, position : 2048};
    this->dummy_item_[0][5] = {id : 6, position : 2048};
    this->dummy_item_[0][6] = {id : 7, position : 2048};
    this->dummy_item_[0][7] = {id : 8, position : 2048};
    this->dummy_item_[0][8] = {id : 9, position : 2048};
    this->dummy_item_[0][9] = {id : 10, position : 2048};
    this->dummy_item_[0][10] = {id : 11, position : 2048};
    this->dummy_item_[0][11] = {id : 12, position : 2048};
    this->dummy_item_[0][12] = {id : 13, position : 2048};
    this->dummy_item_[0][13] = {id : 14, position : 2048};
    this->dummy_item_[0][14] = {id : 15, position : 2048};
    this->dummy_item_[0][15] = {id : 16, position : 2048};
    this->dummy_item_[0][16] = {id : 17, position : 2048};
    this->dummy_item_[0][17] = {id : 18, position : 2048};
    this->dummy_item_[0][18] = {id : 19, position : 2048};
    this->dummy_item_[0][19] = {id : 20, position : 2048};

    this->dummy_item_[1][0] = {id : 1, position : 2248};
    this->dummy_item_[1][1] = {id : 2, position : 2048};
    this->dummy_item_[1][2] = {id : 3, position : 2048};
    this->dummy_item_[1][3] = {id : 4, position : 2048};
    this->dummy_item_[1][4] = {id : 5, position : 2048};
    this->dummy_item_[1][5] = {id : 6, position : 2048};
    this->dummy_item_[1][6] = {id : 7, position : 2048};
    this->dummy_item_[1][7] = {id : 8, position : 2048};
    this->dummy_item_[1][8] = {id : 9, position : 2048};
    this->dummy_item_[1][9] = {id : 10, position : 2048};
    this->dummy_item_[1][10] = {id : 11, position : 2048};
    this->dummy_item_[1][11] = {id : 12, position : 2048};
    this->dummy_item_[1][12] = {id : 13, position : 2048};
    this->dummy_item_[1][13] = {id : 14, position : 2048};
    this->dummy_item_[1][14] = {id : 15, position : 2048};
    this->dummy_item_[1][15] = {id : 16, position : 2048};
    this->dummy_item_[1][16] = {id : 17, position : 2048};
    this->dummy_item_[1][17] = {id : 18, position : 2048};
    this->dummy_item_[1][18] = {id : 19, position : 2048};
    this->dummy_item_[1][19] = {id : 20, position : 2048};

    this->dummy_item_[2][0] = {id : 1, position : 2048};
    this->dummy_item_[2][1] = {id : 2, position : 2048};
    this->dummy_item_[2][2] = {id : 3, position : 2048};
    this->dummy_item_[2][3] = {id : 4, position : 2048};
    this->dummy_item_[2][4] = {id : 5, position : 2048};
    this->dummy_item_[2][5] = {id : 6, position : 2048};
    this->dummy_item_[2][6] = {id : 7, position : 2048};
    this->dummy_item_[2][7] = {id : 8, position : 2048};
    this->dummy_item_[2][8] = {id : 9, position : 2048};
    this->dummy_item_[2][9] = {id : 10, position : 2048};
    this->dummy_item_[2][10] = {id : 11, position : 2048};
    this->dummy_item_[2][11] = {id : 12, position : 2048};
    this->dummy_item_[2][12] = {id : 13, position : 2048};
    this->dummy_item_[2][13] = {id : 14, position : 2048};
    this->dummy_item_[2][14] = {id : 15, position : 2048};
    this->dummy_item_[2][15] = {id : 16, position : 2048};
    this->dummy_item_[2][16] = {id : 17, position : 2048};
    this->dummy_item_[2][17] = {id : 18, position : 2048};
    this->dummy_item_[2][18] = {id : 19, position : 2048};
    this->dummy_item_[2][19] = {id : 20, position : 2048};

    this->dummy_item_[3][0] = {id : 1, position : 2048};
    this->dummy_item_[3][1] = {id : 2, position : 2048};
    this->dummy_item_[3][2] = {id : 3, position : 2048};
    this->dummy_item_[3][3] = {id : 4, position : 2048};
    this->dummy_item_[3][4] = {id : 5, position : 2048};
    this->dummy_item_[3][5] = {id : 6, position : 2048};
    this->dummy_item_[3][6] = {id : 7, position : 2048};
    this->dummy_item_[3][7] = {id : 8, position : 2048};
    this->dummy_item_[3][8] = {id : 9, position : 2048};
    this->dummy_item_[3][9] = {id : 10, position : 2048};
    this->dummy_item_[3][10] = {id : 11, position : 2048};
    this->dummy_item_[3][11] = {id : 12, position : 2048};
    this->dummy_item_[3][12] = {id : 13, position : 2048};
    this->dummy_item_[3][13] = {id : 14, position : 2048};
    this->dummy_item_[3][14] = {id : 15, position : 2048};
    this->dummy_item_[3][15] = {id : 16, position : 2048};
    this->dummy_item_[3][16] = {id : 17, position : 2048};
    this->dummy_item_[3][17] = {id : 18, position : 2048};
    this->dummy_item_[3][18] = {id : 19, position : 2048};
    this->dummy_item_[3][19] = {id : 20, position : 2048};

    this->dummy_item_[4][0] = {id : 1, position : 2048};
    this->dummy_item_[4][1] = {id : 2, position : 2048};
    this->dummy_item_[4][2] = {id : 3, position : 2048};
    this->dummy_item_[4][3] = {id : 4, position : 2048};
    this->dummy_item_[4][4] = {id : 5, position : 2048};
    this->dummy_item_[4][5] = {id : 6, position : 2048};
    this->dummy_item_[4][6] = {id : 7, position : 2048};
    this->dummy_item_[4][7] = {id : 8, position : 2048};
    this->dummy_item_[4][8] = {id : 9, position : 2048};
    this->dummy_item_[4][9] = {id : 10, position : 2048};
    this->dummy_item_[4][10] = {id : 11, position : 2048};
    this->dummy_item_[4][11] = {id : 12, position : 2048};
    this->dummy_item_[4][12] = {id : 13, position : 2048};
    this->dummy_item_[4][13] = {id : 14, position : 2048};
    this->dummy_item_[4][14] = {id : 15, position : 2048};
    this->dummy_item_[4][15] = {id : 16, position : 2048};
    this->dummy_item_[4][16] = {id : 17, position : 2048};
    this->dummy_item_[4][17] = {id : 18, position : 2048};
    this->dummy_item_[4][18] = {id : 19, position : 2048};
    this->dummy_item_[4][19] = {id : 20, position : 2048};

    this->dummy_item_[5][0] = {id : 1, position : 2048};
    this->dummy_item_[5][1] = {id : 2, position : 2048};
    this->dummy_item_[5][2] = {id : 3, position : 2048};
    this->dummy_item_[5][3] = {id : 4, position : 2048};
    this->dummy_item_[5][4] = {id : 5, position : 2048};
    this->dummy_item_[5][5] = {id : 6, position : 2048};
    this->dummy_item_[5][6] = {id : 7, position : 2048};
    this->dummy_item_[5][7] = {id : 8, position : 2048};
    this->dummy_item_[5][8] = {id : 9, position : 2048};
    this->dummy_item_[5][9] = {id : 10, position : 2048};
    this->dummy_item_[5][10] = {id : 11, position : 2048};
    this->dummy_item_[5][11] = {id : 12, position : 2048};
    this->dummy_item_[5][12] = {id : 13, position : 2048};
    this->dummy_item_[5][13] = {id : 14, position : 2048};
    this->dummy_item_[5][14] = {id : 15, position : 2048};
    this->dummy_item_[5][15] = {id : 16, position : 2048};
    this->dummy_item_[5][16] = {id : 17, position : 2048};
    this->dummy_item_[5][17] = {id : 18, position : 2048};
    this->dummy_item_[5][18] = {id : 19, position : 2048};
    this->dummy_item_[5][19] = {id : 20, position : 2048};

    this->dummy_item_[6][0] = {id : 1, position : 2048};
    this->dummy_item_[6][1] = {id : 2, position : 2048};
    this->dummy_item_[6][2] = {id : 3, position : 2048};
    this->dummy_item_[6][3] = {id : 4, position : 2048};
    this->dummy_item_[6][4] = {id : 5, position : 2048};
    this->dummy_item_[6][5] = {id : 6, position : 2048};
    this->dummy_item_[6][6] = {id : 7, position : 2048};
    this->dummy_item_[6][7] = {id : 8, position : 2048};
    this->dummy_item_[6][8] = {id : 9, position : 2048};
    this->dummy_item_[6][9] = {id : 10, position : 2048};
    this->dummy_item_[6][10] = {id : 11, position : 2048};
    this->dummy_item_[6][11] = {id : 12, position : 2048};
    this->dummy_item_[6][12] = {id : 13, position : 2048};
    this->dummy_item_[6][13] = {id : 14, position : 2048};
    this->dummy_item_[6][14] = {id : 15, position : 2048};
    this->dummy_item_[6][15] = {id : 16, position : 2048};
    this->dummy_item_[6][16] = {id : 17, position : 2048};
    this->dummy_item_[6][17] = {id : 18, position : 2048};
    this->dummy_item_[6][18] = {id : 19, position : 2048};
    this->dummy_item_[6][19] = {id : 20, position : 2048};

    this->dummy_item_[7][0] = {id : 1, position : 2048};
    this->dummy_item_[7][1] = {id : 2, position : 2048};
    this->dummy_item_[7][2] = {id : 3, position : 2048};
    this->dummy_item_[7][3] = {id : 4, position : 2048};
    this->dummy_item_[7][4] = {id : 5, position : 2048};
    this->dummy_item_[7][5] = {id : 6, position : 2048};
    this->dummy_item_[7][6] = {id : 7, position : 2048};
    this->dummy_item_[7][7] = {id : 8, position : 2048};
    this->dummy_item_[7][8] = {id : 9, position : 2048};
    this->dummy_item_[7][9] = {id : 10, position : 2048};
    this->dummy_item_[7][10] = {id : 11, position : 2048};
    this->dummy_item_[7][11] = {id : 12, position : 2048};
    this->dummy_item_[7][12] = {id : 13, position : 2048};
    this->dummy_item_[7][13] = {id : 14, position : 2048};
    this->dummy_item_[7][14] = {id : 15, position : 2048};
    this->dummy_item_[7][15] = {id : 16, position : 2048};
    this->dummy_item_[7][16] = {id : 17, position : 2048};
    this->dummy_item_[7][17] = {id : 18, position : 2048};
    this->dummy_item_[7][18] = {id : 19, position : 2048};
    this->dummy_item_[7][19] = {id : 20, position : 2048};
}

Dummy::~Dummy() {}

}
