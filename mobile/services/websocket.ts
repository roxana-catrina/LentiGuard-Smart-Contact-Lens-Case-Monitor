import { Client } from "@stomp/stompjs";

const WS_URL = "ws://192.168.1.128:8080/ws";

export function connectWebSocket(
  deviceId: number,
  onMessage: (message: string) => void
) {
  console.log("CREATING STOMP CLIENT");
  console.log("WS URL:", WS_URL);

  const client = new Client({
    webSocketFactory: () => {
  console.log("CREATING WEBSOCKET FROM FACTORY");
  return new WebSocket(WS_URL);
},

    reconnectDelay: 5000,
 forceBinaryWSFrames: true,
appendMissingNULLonIncoming: true,
    debug: (message) => {
      console.log("STOMP DEBUG:", message);
    },

    onConnect: () => {
      console.log("WEBSOCKET CONNECTED");

      client.subscribe(
        `/topic/device/${deviceId}`,
        (message) => {
          console.log("WEBSOCKET MESSAGE:", message.body);
          onMessage(message.body);
        }
      );
    },

    onStompError: (frame) => {
      console.error("STOMP ERROR:", frame.headers["message"]);
      console.error("STOMP ERROR BODY:", frame.body);
    },

    onWebSocketError: (error) => {
      console.error("WEBSOCKET ERROR:", error);
    },

    onWebSocketClose: (event) => {
      console.log(
        "WEBSOCKET CLOSED:",
        event.code,
        event.reason
      );
    },
  });

  console.log("ACTIVATING STOMP CLIENT");

  client.activate();

  console.log("AFTER ACTIVATE");

  return client;
}