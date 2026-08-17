export function testWebSocket() {
  console.log("CREATING RAW WEBSOCKET");

  const ws = new WebSocket("ws://192.168.1.128:8080/ws");

  ws.onopen = () => {
    console.log("RAW WEBSOCKET OPENED");

    const frame =
      "CONNECT\n" +
      "accept-version:1.2,1.1,1.0\n" +
      "heart-beat:10000,10000\n" +
      "\n" +
      "\0";

    console.log("FRAME LENGTH:", frame.length);
    console.log("FRAME LAST CHAR:", frame.charCodeAt(frame.length - 1));

    ws.send(frame);

    console.log("RAW STOMP CONNECT SENT");
  };

  ws.onmessage = (event) => {
    console.log("RAW WEBSOCKET MESSAGE:", event.data);
  };

  ws.onerror = (error) => {
    console.error("RAW WEBSOCKET ERROR:", error);
  };

  ws.onclose = (event) => {
    console.log("RAW WEBSOCKET CLOSED:", event.code, event.reason);
  };

  return ws;
}