import json

def verify_and_correct_json(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        data = json.load(file)

    estaciones = data["estaciones"]
    conexiones = data["conexiones"]
    transferencias = data["transferencias"]

    # Crear un conjunto de estaciones para verificar IDs y nombres
    estacion_ids = set()
    estacion_nombres = set()

    for estacion in estaciones:
        estacion_ids.add(estacion["id"])
        estacion_nombres.add(estacion["nombre"])

    # Verificar y corregir conexiones bidireccionales
    conexiones_set = set()
    for conexion in conexiones:
        origen = conexion["origen"]
        destino = conexion["destino"]
        tiempo = conexion["tiempo"]

        if origen not in estacion_ids or destino not in estacion_ids:
            print(f"Error: Estación {origen} o {destino} no encontrada en estaciones.")
            continue

        conexiones_set.add((origen, destino, tiempo))
        conexiones_set.add((destino, origen, tiempo))

    # Verificar y corregir transferencias bidireccionales
    transferencias_set = set()
    for transferencia in transferencias:
        origen = transferencia["origen"]
        destino = transferencia["destino"]
        tiempo_extra = transferencia["tiempo_extra"]

        if origen not in estacion_ids or destino not in estacion_ids:
            print(f"Error: Estación {origen} o {destino} no encontrada en estaciones.")
            continue

        transferencias_set.add((origen, destino, tiempo_extra))
        transferencias_set.add((destino, origen, tiempo_extra))

    # Crear listas finales de conexiones y transferencias
    conexiones_finales = [{"origen": o, "destino": d, "tiempo": t} for (o, d, t) in conexiones_set]
    transferencias_finales = [{"origen": o, "destino": d, "tiempo_extra": t} for (o, d, t) in transferencias_set]

    # Actualizar el JSON con las conexiones y transferencias corregidas
    data["conexiones"] = conexiones_finales
    data["transferencias"] = transferencias_finales

    # Guardar el JSON corregido
    with open('metrobus_data_corrected.json', 'w', encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=4)

    print("Archivo JSON corregido y guardado como 'metrobus_data_corrected.json'.")

# Verificar y corregir el archivo JSON
verify_and_correct_json('metrobus_data.json')
