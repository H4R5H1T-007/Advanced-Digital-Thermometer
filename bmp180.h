#ifndef bmp180_h
#define bmp180_h


#define bmp180_read_addr            0xEF
#define bmp180_write_addr           0xEE
#define control_reg_addr            0xF4

#define temperature_sel             0x2E
#define pressure_0_sel              0x34
#define pressure_1_sel              0x74
#define pressure_2_sel              0xB4
#define pressure_3_sel              0xF4

#define bmp180_mode_0               0
#define bmp180_mode_1               1
#define bmp180_mode_2               2
#define bmp180_mode_3               3

#define wait_temperature            4.5f
#define wait_pressure_mode_0        4.5f
#define wait_pressure_mode_1        7.5f
#define wait_pressure_mode_2        13.5f
#define wait_pressure_mode_3        25.5f

#define out_msb                     0xF6
#define out_lsb                     0xF7
#define out_xlsb                    0xF8

const uint16_t bmp180_coeff_addr[11] = {
    0xAAAB, 0xACAD, 0xAEAF, 0xB0B1, 0xB2B3,
    0xB4B5, 0xB6B7, 0xB8B9, 0xBABB, 0xBCBD,
    0xBEBF
};

const int32_t pressure_sea_level = 101325;

typedef struct {
    short AC1;
    short AC2;
    short AC3;
    uint16_t AC4;
    uint16_t AC5;
    uint16_t AC6;
    short B1;
    short B2;
    long B5;
    short MB;
    short MC;
    short MD;
} calibration_coeff;

typedef struct {
    short mode;
    long UT;
    long UP;
    long temperature;
    long pressure;
    float altitude;
    calibration_coeff calib_coeffs;
} bmp180;

/* Function Prototypes */

void init_sensor(short);
long calculate_temperature(void);
void calculate_pressure(void);
long read_temperature(void);
long read_pressure(void);
void read_coeffs(void);
void calculate(void);
void calculate_altitude(void);

#endif /* bmp180_h */