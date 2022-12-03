#ifndef DUMMY_HPP_
#define DUMMY_HPP_

#include "arpis_server/joint/joint.hpp"

namespace arpis_server {

class Dummy : public Joint {
public:
    Dummy();
    void load_data();
    arpis publish();
    void increment() override;
    int get_iteration() override;
    void set_position(int pos) override;
    ~Dummy() override;
protected:
private:
    int dummy_readed = 0;
    arpis_transfer_item dummy_item_[1000][20];
};

}

#endif