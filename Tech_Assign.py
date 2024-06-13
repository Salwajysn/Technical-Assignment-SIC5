from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/sensor', methods=['POST'])
def sensor_data():
    data = request.get_json()

    if not data or 'sensor_value' not in data:
        return jsonify({'error': 'Invalid data'}), 400

    sensor_value = data['sensor_value']
    print(f'Received sensor value: {sensor_value}')

    # Process the sensor value if needed and return a response
    response = {
        'status': 'success',
        'message': 'Sensor data received',
        'received_value': sensor_value
    }
    
    return jsonify(response), 200

if __name__ == '__main__':
    app.run(debug=True, host='172.23.13.4', port=5000)
