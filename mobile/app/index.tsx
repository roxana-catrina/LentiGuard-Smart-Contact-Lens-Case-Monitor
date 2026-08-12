import { useEffect, useState } from "react";
import { Text, View } from "react-native";
import AlarmCard from "../components/AlarmCard";
import BatteryCard from "../components/BatteryCard";
import LensCaseCard from "../components/LensCaseCard";
import LidCard from "../components/LidCard";
import WifiCard from "../components/WifiCard";
import { getDashboard } from "../services/api";
export default function HomeScreen() {
  const [batteryLevel, setBatteryLevel] = useState(100);
  const [lidOpen, setLidOpen] = useState(false);
  const [lensCasePresent, setLensCasePresent] = useState(true);
  const [alarmActive, setAlarmActive] = useState(false);
  const [wifiConnected, setWifiConnected] = useState(true);



useEffect(() => {
  console.log("USE EFFECT STARTED");

  getDashboard(1)
  .then((data) => {
    setBatteryLevel(data.batteryLevel);
    setLidOpen(data.lidOpen);
    setLensCasePresent(data.lensCasePresent);
    setAlarmActive(data.alarmActive);
    setWifiConnected(data.wifiConnected);
  })
  .catch((error) => {
    console.error("DASHBOARD ERROR:", error);
  });
}, []);


  return (
  <View
    style={{
      flex: 1,
      backgroundColor: "#F4F7FA",
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

  </View>
);
}