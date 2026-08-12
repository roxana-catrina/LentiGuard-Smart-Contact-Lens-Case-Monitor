import { DashboardData } from "../types/Dashboard";

const API_URL = "http://192.168.1.129:8080";

export async function getDashboard(
  deviceId: number
): Promise<DashboardData> {
  const response = await fetch(
    `${API_URL}/api/dashboard/${deviceId}`
  );

  if (!response.ok) {
    throw new Error("Failed to fetch dashboard");
  }

  return await response.json();
}