#ifndef TACHIMAWARI_HPP_
#define TACHIMAWARI_HPP_

#include <memory>
#include "arpis_server/joint/joint.hpp"
#include "tachimawari/control/control.hpp"
#include "tachimawari/joint/joint.hpp"
#include "tachimawari/joint/model/joint_id.hpp"
#include "tachimawari/joint/protocol_1/mx28_address.hpp"
#include "rclcpp/rclcpp.hpp"
#include "arpis_server/model/arpis.hpp"
#include "arpis_server/joint/joint.hpp"

namespace arpis_server{

class Tachimawari : public Joint {
public:    
    Tachimawari(int mode);
    void load_data();
    arpis publish();
    ~Tachimawari() override;
protected:
    std::shared_ptr<::tachimawari::control::ControlManager> control_manager_;
    std::shared_ptr<::tachimawari::joint::JointManager> joint_manager_;
private:
    int mode;
};

}

#endif