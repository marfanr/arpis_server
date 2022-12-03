#include "arpis_server/joint/dummy.hpp"

namespace arpis_server {

arpis Dummy::publish()
{
    arpis item;
    auto dummy = dummy_item_[dummy_readed];
    for (int i = 0; i < 20; i++)
    {
        item.i[i].id = dummy[i].id;
        item.i[i].position = dummy[i].position;
    }
    return item;
}

void Dummy::increment()
{
    this->dummy_readed += 1;
}

void Dummy::set_position(int pos)
{
    this->dummy_readed = pos;
}

int Dummy::get_iteration()
{
    return this->dummy_readed;
}

}