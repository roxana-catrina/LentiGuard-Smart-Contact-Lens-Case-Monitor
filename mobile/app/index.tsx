import { useEffect, useState } from "react";
import { ScrollView, Text } from "react-native";
import AlarmCard from "../components/AlarmCard";
import BatteryCard from "../components/BatteryCard";
import EventsCard from "../components/EventsCard";
import LensCaseCard from "../components/LensCaseCard";
import LidCard from "../components/LidCard";
import WifiCard from "../components/WifiCard";
import { getDashboard } from "../services/api";
import { DashboardEvent } from "../types/Dashboard";
export default function HomeScreen() {
  const [batteryLevel, setBatteryLevel] = useState(100);
  const [lidOpen, setLidOpen] = useState(false);
  const [lensCasePresent, setLensCasePresent] = useState(true);
  const [alarmActive, setAlarmActive] = useState(false);
  const [wifiConnected, setWifiConnected] = useState(true);
  const [events, setEvents] = useState<DashboardEvent[]>([]);


useEffect(() => {
  console.log("USE EFFECT STARTED");

  getDashboard(1)
  .then((data) => {
     console.log("DASHBOARD DATA:", data);
      console.log("EVENTS:", data.lastEvents);

    setBatteryLevel(data.batteryLevel);
    setLidOpen(data.lidOpen);
    setLensCasePresent(data.lensCasePresent);
    setAlarmActive(data.alarmActive);
    setWifiConnected(data.wifiConnected);
    setEvents(data.lastEvents);
  })
  .catch((error) => {
    console.error("DASHBOARD ERROR:", error);
  });
}, []);


  return (
  <ScrollView
  style={{
    flex: 1,
    backgroundColor: "#F4F7FA",
  }}
  contentContainerStyle={{
    padding: 20,
  }}
>
    <Text
      style={{
        fontSize: 28,
        fontWeight: "bold",
        marginTop: 40,
      }}
    >
      LentiGuard
    </Text>

    <Text>Test LentiGuard</Text>
    
  <BatteryCard batteryLevel={batteryLevel} />


<LidCard lidOpen={lidOpen} />
<LensCaseCard lensCasePresent={lensCasePresent} />
<AlarmCard alarmActive={alarmActive} />
<WifiCard wifiConnected={wifiConnected} />
<EventsCard events={events} />
  </ScrollView>
);
}