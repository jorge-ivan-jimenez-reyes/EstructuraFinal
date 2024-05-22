import json

def ensure_bidirectional(json_data):
    conexiones = json_data["conexiones"]
    bidirectional_connections = []
    for connection in conexiones:
        origin = connection["origen"]
        dest = connection["destino"]
        time = connection["tiempo"]
        bidirectional_connections.append(connection)
        reverse_connection = {"origen": dest, "destino": origin, "tiempo": time}
        if reverse_connection not in conexiones:
            bidirectional_connections.append(reverse_connection)
    json_data["conexiones"] = bidirectional_connections

    transferencias = json_data["transferencias"]
    bidirectional_transfers = []
    for transfer in transferencias:
        origin = transfer["origen"]
        dest = transfer["destino"]
        extra_time = transfer["tiempo_extra"]
        bidirectional_transfers.append(transfer)
        reverse_transfer = {"origen": dest, "destino": origin, "tiempo_extra": extra_time}
        if reverse_transfer not in transferencias:
            bidirectional_transfers.append(reverse_transfer)
    json_data["transferencias"] = bidirectional_transfers

    return json_data

# Load JSON file
with open('metrobus_data.json', 'r') as file:
    data = json.load(file)

# Ensure bidirectional connections and transfers
corrected_data = ensure_bidirectional(data)

# Save corrected JSON to a new file
with open('metrobus_data_corrected.json', 'w') as file:
    json.dump(corrected_data, file, indent=4)

print("JSON file has been verified and corrected successfully.")
