import DateTimePicker from "@react-native-community/datetimepicker";
import { useState } from "react";
import {
  Alert,
  Button,
  Platform,
  Text,
  View,
} from "react-native";
import { setAlarm } from "../services/api";

type AlarmCardProps = {
  alarmActive: boolean;
};

export default function AlarmCard({
  alarmActive,
}: AlarmCardProps) {
  const [alarmTime, setAlarmTime] = useState(new Date());
  const [showPicker, setShowPicker] = useState(false);
  const [alarmEnabled, setAlarmEnabled] = useState(false);

  const handleTimeChange = (
    event: any,
    selectedTime?: Date
  ) => {
    setShowPicker(false);

    if (selectedTime) {
      setAlarmTime(selectedTime);
    }
  };

  const handleSetAlarm = async () => {
    try {
      const hours = alarmTime
        .getHours()
        .toString()
        .padStart(2, "0");

      const minutes = alarmTime
        .getMinutes()
        .toString()
        .padStart(2, "0");

      const time = `${hours}:${minutes}`;

      console.log("SETTING ALARM:", time);

      const result = await setAlarm(
        1,
        time,
        true
      );

      console.log("ALARM SET:", result);

      setAlarmEnabled(true);

      Alert.alert(
        "Alarmă",
        `Alarma a fost setată pentru ${time}`
      );

    } catch (error) {
      console.error("SET ALARM ERROR:", error);

      Alert.alert(
        "Eroare",
        "Nu am putut seta alarma."
      );
    }
  };

  return (
    <View
      style={{
        backgroundColor: "white",
        padding: 20,
        marginTop: 20,
        borderRadius: 15,
      }}
    >
      <Text
        style={{
          fontSize: 18,
          fontWeight: "bold",
        }}
      >
        Alarmă
      </Text>

      <Text
        style={{
          fontSize: 24,
          marginTop: 10,
        }}
      >
        {alarmActive ? "SUNĂ" : "OPRITĂ"}
      </Text>

      <Text
        style={{
          fontSize: 28,
          marginTop: 15,
          textAlign: "center",
        }}
      >
        {alarmTime
          .getHours()
          .toString()
          .padStart(2, "0")}
        :
        {alarmTime
          .getMinutes()
          .toString()
          .padStart(2, "0")}
      </Text>

      <View style={{ marginTop: 15 }}>
        <Button
          title="Alege ora"
          onPress={() => setShowPicker(true)}
        />
      </View>

      {showPicker && (
        <DateTimePicker
          value={alarmTime}
          mode="time"
          is24Hour={true}
          display={
            Platform.OS === "ios"
              ? "spinner"
              : "default"
          }
          onChange={handleTimeChange}
        />
      )}

      <View style={{ marginTop: 15 }}>
        <Button
          title={
            alarmEnabled
              ? "Alarma este setată"
              : "Setează alarma"
          }
          onPress={handleSetAlarm}
        />
      </View>
    </View>
  );
}