#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h>

constexpr int PWM_FREQUENCY = 50;
constexpr int DUTY_CYCLE = 50;

constexpr int MOTOR_A1_PIN = 1;   // GPIO 18
constexpr int MOTOR_A2_PIN = 24;  // GPIO 5
constexpr int MOTOR_B1_PIN = 26;  // GPIO 12
constexpr int MOTOR_B2_PIN = 27;  // GPIO 6

void move_forward() {
    std::cout << "forward" << '\n';

    pwmWrite(MOTOR_A1_PIN, DUTY_CYCLE);
    pwmWrite(MOTOR_B1_PIN, DUTY_CYCLE);

    digitalWrite(MOTOR_A2_PIN, LOW);
    digitalWrite(MOTOR_B2_PIN, LOW);
}

void move_backward() {
    std::cout << "back" << '\n';

    pwmWrite(MOTOR_A1_PIN, DUTY_CYCLE);
    pwmWrite(MOTOR_B1_PIN, DUTY_CYCLE);

    digitalWrite(MOTOR_A2_PIN, HIGH);
    digitalWrite(MOTOR_B2_PIN, HIGH);
}

void move_left() {
    std::cout << "left" << '\n';

    pwmWrite(MOTOR_A1_PIN, DUTY_CYCLE);
    pwmWrite(MOTOR_B1_PIN, DUTY_CYCLE);

    digitalWrite(MOTOR_A2_PIN, LOW);
    digitalWrite(MOTOR_B2_PIN, HIGH);
}

void move_right() {
    std::cout << "right" << '\n';

    pwmWrite(MOTOR_A1_PIN, DUTY_CYCLE);
    pwmWrite(MOTOR_B1_PIN, DUTY_CYCLE);

    digitalWrite(MOTOR_A2_PIN, HIGH);
    digitalWrite(MOTOR_B2_PIN, LOW);
}

void stop() {
    std::cout << "stop" << '\n';

    pwmWrite(MOTOR_A1_PIN, 0);
    pwmWrite(MOTOR_B1_PIN, 0);
}

int main() {
    wiringPiSetup();

    pinMode(MOTOR_A1_PIN, PWM_OUTPUT);
    pinMode(MOTOR_A2_PIN, OUTPUT);
    pinMode(MOTOR_B1_PIN, PWM_OUTPUT);
    pinMode(MOTOR_B2_PIN, OUTPUT);

    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(100);
    pwmSetClock(384);

    try {
        move_forward();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        stop();
        move_backward();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        stop();
        move_left();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        stop();
        move_right();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        stop();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } catch (...) {
        std::cout << "Exception occurred" << '\n';
    }

    stop();
    pinMode(MOTOR_A1_PIN, INPUT);
    pinMode(MOTOR_B1_PIN, INPUT);

    return 0;
}
