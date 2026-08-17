import { connectWebSocket } from "@/services/websocket";
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

useEffect(() => {
  console.log("WEBSOCKET EFFECT STARTED");

 const client = connectWebSocket(1, (message) => {
  console.log("MESSAGE FROM WEBSOCKET:", message);

  if (message === "LID_OPENED") {
    setLidOpen(true);
  }

  if (message === "LID_CLOSED") {
    setLidOpen(false);
  }

  if (message === "LENS_CASE_INSERTED") {
    setLensCasePresent(true);
  }

  if (message === "LENS_CASE_REMOVED") {
    setLensCasePresent(false);
  }
  setEvents((prevEvents) => [
  {
    id: Date.now(),
    eventType: message,
    createdAt: new Date().toISOString(),
  },
  ...prevEvents,
].slice(0, 10));
});

  console.log("WEBSOCKET CLIENT CREATED");

  return () => {
    console.log("WEBSOCKET CLEANUP");
    //client.deactivate();
  };
  
}, []);
/*
useEffect(() => {
  console.log("RAW TEST STARTED");

  const ws = testWebSocket();

  return () => {
    ws.close();
  };
}, []);
*/
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