from flask import Flask, render_template, request, jsonify 


app = Flask(__name__)

val = 0

@app.route('/', methods=['GET','POST'])
def index():
    if request.method == "POST":
        value =  request.form['slider']
        global val
        val = int(value)
    return render_template('index.html', motor_angle=val)


@app.route('/api')
def api():
    return jsonify(val)
    
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')