//
// Created by Aaryan Gulia on 31/01/2024.
//
#include "iostream"
#include "Ball.h"
#include <mach-o/dyld.h>
#include <libgen.h>
#include <CoreFoundation/CoreFoundation.h>

std::string getExecutablePath() {
    CFURLRef bundleURL = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef bundlePathString = CFURLCopyFileSystemPath(bundleURL, kCFURLPOSIXPathStyle);
    CFRelease(bundleURL);

    const char *bundlePathCString = CFStringGetCStringPtr(bundlePathString, kCFStringEncodingUTF8);
    std::string bundlePath(bundlePathCString);

    CFRelease(bundlePathString);

    return bundlePath;
}

Ball::Ball(float xPos, float yPos, float xSpeed, float ySpeed, int radius) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
    this->radius = radius;
    std::string path = getExecutablePath() + "/sounds/Retro_Blop_22.wav";
    std::cout << path << std::endl;
    collisionSound = LoadSound(path.c_str());
    path = getExecutablePath() + "/sounds/Retro_Negative_Short_23.wav";
    exitScreenSound = LoadSound(path.c_str());
}

void Ball::move() {
    xPos += xSpeed;
    yPos += ySpeed;
}

void Ball::reset(int screenWidth, int screenHeight) {
    xPos = screenWidth/2;
    yPos = screenHeight/2;
    xSpeed = -xSpeed;
}

bool Ball::checkBatCollision(int batX, int batY, int batWidth, int batHeight, int player) {
    if(player == 1 && xPos - radius <= batX + batWidth && yPos >= batY && yPos <= batY + batHeight){
        xSpeed = -xSpeed;
        xPos = batX + batWidth + radius + 1; // Add offset to the ball's position
        PlaySound(collisionSound);
        return true;
    }
    if(player == 2 && xPos + radius >= batX && yPos >= batY && yPos <= batY + batHeight){
        xSpeed = -xSpeed;
        xPos = batX - radius - 1; // Add offset to the ball's position
        PlaySound(collisionSound);
        return true;
    }
    else return false;
}

bool Ball::checkWallCollision(int screenWidth, int screenHeight) {
    if(yPos - radius <= 0 || yPos + radius >= screenHeight){
        ySpeed = -ySpeed;
    }
    if(xPos - radius <= 0 || xPos + radius >= screenWidth){
        PlaySound(exitScreenSound);
        reset(screenWidth, screenHeight);
        return true;
    }
    return false;
}

void Ball::draw() {
    DrawCircle(xPos, yPos, radius, BLACK);
}

void Ball::setXSpeed(float xSpeed) {
    this->xSpeed = xSpeed;
}
void Ball::setYSpeed(float ySpeed) {
    this->ySpeed = ySpeed;
}
float Ball::getXPos() {
    return xPos;
}
float Ball::getYPos() {
    return yPos;
}
float Ball::getXSpeed() {
    return xSpeed;
}
float Ball::getYSpeed() {
    return ySpeed;
}

void Ball::setXPos(float xPos) {
    this->xPos = xPos;
}
void Ball::setYPos(float yPos) {
    this->yPos = yPos;
}