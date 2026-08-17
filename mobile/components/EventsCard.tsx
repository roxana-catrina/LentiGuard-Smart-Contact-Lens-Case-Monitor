import { Text, View } from "react-native";

type Event = {
  id: number;
  eventType: string;
  createdAt: string;
};

type EventsCardProps = {
  events: Event[];
};

export default function EventsCard({
  events,
}: EventsCardProps) {
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
          fontSize: 20,
          fontWeight: "bold",
        }}
      >
        Last Events
      </Text>

      {events.map((event) => (
        <View
          key={event.id}
          style={{
            marginTop: 15,
          }}
        >
          <Text
            style={{
              fontSize: 16,
              fontWeight: "bold",
            }}
          >
            {event.eventType}
          </Text>

          <Text
            style={{
              fontSize: 14,
              marginTop: 4,
            }}
          >
            {event.createdAt}
          </Text>
        </View>
      ))}
    </View>
  );
}