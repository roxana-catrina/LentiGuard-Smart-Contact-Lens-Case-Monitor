import { Text, View } from "react-native";

type LidCardProps = {
  lidOpen: boolean;
};

export default function LidCard({
  lidOpen,
}: LidCardProps) {
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
        Lid
      </Text>

      <Text
        style={{
          fontSize: 24,
          marginTop: 10,
        }}
      >
        {lidOpen ? "Open" : "Closed"}
      </Text>
    </View>
  );
}