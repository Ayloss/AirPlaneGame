#pragma once
#include "DifficultyControl.h"
//难度等级
float difficultyLevel;

//敌机基础数据
const int speedBaseValue[3] = { 100,80,50 };//基础速度
const int speedValueRange[3] = { 250,150,100 };//速度变化范围
const int scoreValue[3] = { 1000,5000,30000 };//分数
const int lifeValue[3] = { 1,5,9 };//生命值