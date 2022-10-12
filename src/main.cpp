#include <easy_tcp.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <gamepad.h>
#include <math.h>

using namespace easy_tcp;
using namespace std;
using namespace gamepad;


#define MAX 500
#define MIN 0
#define JOYSTICK_MAX 37267

struct MyData {
    int32_t left, right;
    int32_t speed = 0;
    //bool gamepad_mode = true;
} pwm_data;

//char* message;
//size_t message_size = 8;

int safe_sqrt(int num) {
    if ( num < 0 )
        return -sqrt(abs(num));
    return sqrt(num);
}

int get_normalized_speed(float speed) {
    return speed/JOYSTICK_MAX * MAX; //remove safe_sqrt
}

int main(){
    Client c;
    string robot_ip = "192.168.137.154";
    string device = "/dev/input/js0";
    if (!c.connect(robot_ip, 4500)) {
        cout << "error connecting to robot" << endl;
        return -1;
    }

    Gamepad* j = new Gamepad(device);
    int pleft = 0;
    int pright = 0;
    bool update;

    while (true) {
        update = false;

        float left = get_normalized_speed(j->axes[1]);
        float right = get_normalized_speed(j->axes[4] ) * 1.3;

        if (pwm_data.left != left || pwm_data.right != right) {

            pwm_data.left = left;
            pwm_data.right = right;

            //cout << "gamepad left: "<< -j->axes[1] << " right: "<<  -j->axes[4]<< endl;
            cout << "robot left: " << left << " right: " << right << endl;

            ((Connection) c).send_data((char *) &pwm_data, sizeof(pwm_data));
            //c.receive_data();
            //c.received_data(message, message_size);
        }

        if (j->buttons[8].state == 1) { //kill button X?
                break;
                c.disconnect();
        }
        usleep(10);
    }
}



