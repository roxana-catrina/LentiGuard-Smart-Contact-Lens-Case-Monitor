import { Text, View } from "react-native";

type WifiCardProps = {
  wifiConnected: boolean;
};

export default function WifiCard({
  wifiConnected,
}: WifiCardProps) {
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
        WiFi
      </Text>

      <Text
        style={{
          fontSize: 24,
          marginTop: 10,
        }}
      >
        {wifiConnected ? "Connected" : "Disconnected"}
      </Text>
    </View>
  );
}