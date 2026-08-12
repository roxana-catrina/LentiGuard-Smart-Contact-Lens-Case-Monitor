import { useState } from "react";
import { Button, Text, View } from "react-native";
import AlarmCard from "./components/AlarmCard";
import BatteryCard from "./components/BatteryCard";
import LensCaseCard from "./components/LensCaseCard";
import LidCard from "./components/LidCard";

import WifiCard from "./components/WifiCard";
export default function HomeScreen() {
  const [batteryLevel, setBatteryLevel] = useState(100);
  const [lidOpen, setLidOpen] = useState(false);
  const [lensCasePresent, setLensCasePresent] = useState(true);
  const [alarmActive, setAlarmActive] = useState(false);
  const [wifiConnected, setWifiConnected] = useState(true);

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

<Button
  title="Decrease battery"
  onPress={() => setBatteryLevel(batteryLevel - 10)}
/>
<LidCard lidOpen={lidOpen} />
<LensCaseCard lensCasePresent={lensCasePresent} />
<AlarmCard alarmActive={alarmActive} />
<WifiCard wifiConnected={wifiConnected} />

  </View>
);
}