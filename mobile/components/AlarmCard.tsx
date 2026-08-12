import { Text, View } from "react-native";

type AlarmCardProps = {
  alarmActive: boolean;
};

export default function AlarmCard({
  alarmActive,
}: AlarmCardProps) {
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
        Alarm
      </Text>

      <Text
        style={{
          fontSize: 24,
          marginTop: 10,
        }}
      >
        {alarmActive ? "ON" : "OFF"}
      </Text>
    </View>
  );
}