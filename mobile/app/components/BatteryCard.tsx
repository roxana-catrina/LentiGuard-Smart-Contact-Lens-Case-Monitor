import { Text, View } from "react-native";

type BatteryCardProps = {
  batteryLevel: number;
};

export default function BatteryCard({
  batteryLevel,
}: BatteryCardProps) {
  return (
    <View>
      <Text>Battery</Text>

      <Text>{batteryLevel}%</Text>
    </View>
  );
}