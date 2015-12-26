
#ifndef __APP_H__
#define __APP_H__

#include "stdint.h"

#define SPD_LMT 200
#define MAX_SPD (65535-SPD_LMT)
#define MIN_SPD (0+SPD_LMT)

typedef struct {
	float angle;
	float angleDot;
} angleTypeDef;

typedef struct {
	int16_t m_spd_speed;
	int16_t m_spd_balance;
	int16_t m_spd_direction;
} spdTypeDef;

typedef struct {
	float m_accz;
	float m_gyro;
} balanceDataTypeDef;

//�ɼ�ƽ�⻷��������
void getBalanceData(balanceDataTypeDef* data);

//ƽ�⻷ռ�ձ�
int16_t balanceControl(const balanceDataTypeDef* data);

// �������˲�����
void kalman(const balanceDataTypeDef* data, angleTypeDef* outAngle);

//ʹ��ռ�ձȿ��Ƶ��
void motorControl(const spdTypeDef* spd);

#endif