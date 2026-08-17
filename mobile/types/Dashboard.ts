export type DashboardEvent = {
  id: number;
  eventType: string;
  createdAt: string;
};

export type DashboardData = {
  deviceId: number;
  deviceName: string;
  serialNumber: string;
  batteryLevel: number;
  lidOpen: boolean;
  lensCasePresent: boolean;
  alarmActive: boolean;
  wifiConnected: boolean;
  lastEvents: DashboardEvent[];
};