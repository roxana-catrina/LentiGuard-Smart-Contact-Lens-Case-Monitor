import { DashboardData } from "@/types/Dashboard";

const API_URL = "http://192.168.1.128:8080";
export async function getDashboard(
  deviceId: number
): Promise<DashboardData> {

  console.log("SENDING REQUEST");

  const response = await fetch(
    `${API_URL}/api/dashboard/${deviceId}`
  );

  console.log("RESPONSE STATUS:", response.status);

  const text = await response.text();

  console.log("RESPONSE BODY:", text);

  if (!response.ok) {
    throw new Error("Failed to fetch dashboard");
  }

  return JSON.parse(text);
}