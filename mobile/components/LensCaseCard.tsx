import { Text, View } from "react-native";

type LensCaseCardProps = {
  lensCasePresent: boolean;
};

export default function LensCaseCard({
  lensCasePresent,
}: LensCaseCardProps) {
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
        Lens Case
      </Text>

      <Text
        style={{
          fontSize: 24,
          marginTop: 10,
        }}
      >
        {lensCasePresent ? "Removed" : "Present"}
      </Text>
    </View>
  );
}