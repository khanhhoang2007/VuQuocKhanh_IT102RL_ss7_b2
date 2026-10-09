
#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[100];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice device;
    struct EnergySensor sensor;

    float operatingHours;
    float energyKWh;
    float electricityCost = 0.0f;

    printf("=== SMART HOME IOT ===\n");

    printf("Nhap ma thiet bi: ");
    scanf("%d", &device.deviceID);

    printf("Nhap ten thiet bi: ");
    scanf(" %99[^\n]", device.deviceName);

    printf("Nhap trang thai (1: Bat, 0: Tat): ");
    scanf("%d", &device.status);

    printf("Nhap cong suat dinh muc (kW): ");
    scanf("%f", &device.ratedPowerKW);

    printf("Nhap dien ap (V): ");
    scanf("%f", &sensor.voltageVolts);

    printf("Nhap dong dien (A): ");
    scanf("%f", &sensor.currentAmperes);

    printf("Nhap thoi gian vang nguoi (phut): ");
    scanf("%d", &sensor.unoccupancyMinutes);

    printf("Nhap so gio hoat dong trong thang: ");
    scanf("%f", &operatingHours);

    /* Kiem tra du lieu dau vao */
    if (sensor.voltageVolts < 0 ||
        sensor.currentAmperes < 0 ||
        sensor.unoccupancyMinutes < 0) {
        printf("\nLoi: Du lieu cam bien khong hop le!\n");
        return 1;
    }

    if (device.status != 0 && device.status != 1) {
        printf("\nLoi: Trang thai thiet bi khong hop le!\n");
        return 1;
    }

    if (device.ratedPowerKW <= 0) {
        printf("\nLoi: Cong suat dinh muc phai lon hon 0!\n");
        return 1;
    }

    if (operatingHours <= 0 || operatingHours > 744) {
        printf("\nLoi: So gio hoat dong phai lon hon 0 va khong qua 744!\n");
        return 1;
    }

    /* Xu ly an toan dien va tiet kiem nang luong */
    if (sensor.currentAmperes > 30.0f) {
        device.status = 0;
        printf("\nCANH BAO: Qua tai dong dien, nguy co chay no!\n");
        printf("He thong da ngat dien thiet bi.\n");
    } else if (device.status == 1 &&
               sensor.unoccupancyMinutes >= 15) {
        device.status = 0;
        printf("\nThong bao: Phong vang nguoi tu 15 phut.\n");
        printf("He thong da tat thiet bi de tiet kiem dien.\n");
    }

    /* Tinh dien nang tieu thu */
    energyKWh = device.ratedPowerKW * operatingHours;

    /* Tinh tien dien theo bac thang EVN */
    if (energyKWh <= 50) {
        electricityCost = energyKWh * 1806;
    } else if (energyKWh <= 100) {
        electricityCost = 50 * 1806
                        + (energyKWh - 50) * 1866;
    } else if (energyKWh <= 200) {
        electricityCost = 50 * 1806
                        + 50 * 1866
                        + (energyKWh - 100) * 2167;
    } else {
        electricityCost = 50 * 1806
                        + 50 * 1866
                        + 100 * 2167
                        + (energyKWh - 200) * 2729;
    }

    /* In bao cao */
    printf("\n=== BAO CAO THIET BI ===\n");
    printf("Ma thiet bi: %d\n", device.deviceID);
    printf("Ten thiet bi: %s\n", device.deviceName);
    printf("Trang thai: %s\n",
           device.status == 1 ? "DANG BAT" : "DA TAT");
    printf("Dien ap: %.2f V\n", sensor.voltageVolts);
    printf("Dong dien: %.2f A\n", sensor.currentAmperes);
    printf("Thoi gian vang nguoi: %d phut\n",
           sensor.unoccupancyMinutes);
    printf("Dien nang tieu thu: %.2f kWh\n", energyKWh);
    printf("Tien dien tam tinh: %.0f VND\n", electricityCost);
    printf("(Chua bao gom VAT)\n");

    return 0;
}