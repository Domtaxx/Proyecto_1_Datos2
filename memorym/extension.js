// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require('vscode');
const net = require('net');
const fs = require('fs');
const path = require('path');
const{ execSync } = require('child_process');
var clone = require('git-clone');
const port = 51000;
//const dom = new jsdom.JSDOM(serverDatos());
// this method is called when your extension is activated
// your extension is activated the very first time the command is executed

/**
 * @param {vscode.ExtensionContext} context
 */
function activate(context) {

	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
	console.log('Congratulations, your extension "memorym" is now active!');

	// The command has been defined in the package.json file
	// Now provide the implementation of the command with  registerCommand
	// The commandId parameter must match the command field in package.json
	let disposable = vscode.commands.registerCommand('memorym.memoryManager', function () {
		
		// The code you place here will be executed every time your command is executed
		
		const folderPath = vscode.workspace.workspaceFolders[0].uri.toString().split(":")[1];
		
		fs.writeFile(path.join(folderPath,"main.cpp"),'#include "vsptr.hpp" \n bool is_not_finished = true; \n	void delete_t(){\n		GarbageCollector* gc = GarbageCollector::getGarbageCollector();\n		gc->thread_function(&is_not_finished);\n	};\nint main(){\n	std::thread p(delete_t);\n	Socket_C socket_manager = Socket_C();\n	socket_manager.start();\n	//code here\n	//code end\n	is_not_finished = false;\n	p.join();\n			return 0;\n};'
		,err=>{
			if(err){
				return vscode.window.showErrorMessage("Error creating main file");
			}
			vscode.window.showInformationMessage("Everything is fine!");
		})
		const Fpath = path.join(folderPath,'');
		execSync('git clone https://github.com/Domtaxx/Proyecto_1_Datos2', {
			stdio: [0, 1, 2], // we need this so node will print the command output
			cwd: path.resolve(Fpath, ''), // path to where you want to save the file
		  })
		// Display a message box to the user
		var server = net.createServer();
		server.listen(port, function() {
			console.log(`Server listening for connection requests on socket localhost:${port}`);
		});
		server.on('connection', function(socket) {
			console.log('A new connection has been established.');
		
			// Now that a TCP connection has been established, the server can send data to
			// the socket by writing to its socket.
			socket.write('Hello, socket.');
			
			var datos = "";
			// The server can also receive data from the socket by reading from its socket.
			socket.on('data', function(data) {
				datos = ''+data;
			console.log('Received: '+ data);
			if(datos == "error"){
				vscode.window.showInformationMessage("Error: no se logró crear la conexión");
			}if(datos == "success"){
				vscode.window.showInformationMessage("Se logró crear la conexión con el servidor");
			}else{
				var htmlText = `<!DOCTYPE html>
			<html lang="en">
			<head>
				<meta charset="UTF-8">
				<meta name="viewport" content="width=device-width, initial-scale=1.0">
				<title>Memory Remote</title>
			</head>
			<body>`;
				var valores = datos.split('&');
				var arr_pkgs = valores[0].split('*');
				for(var r = 0;r<arr_pkgs.length;r++){
					var pkg = arr_pkgs[r].split(',');
					htmlText = htmlText + `<p>Variable `+ pkg[0] + `</p> 
					<p style="padding-left: 30px;">Tipo: `+pkg[1]+
					`<br />Valor: ` +pkg[2]+
					`<br />Celda de memoria: ` +pkg[3]+
					`<br />Referencias actuales: ` +pkg[4]+`</p>`;
				}
				var arr_ptrs = valores[1].split('*');
				for(var p = 0;p<arr_ptrs.length;p++){
					var ptr = arr_ptrs[p].split(',');
					//id+","+tipo+","+val+","+addr+","+ref;
					htmlText = htmlText +`<p>Puntero `+ptr[0] + `</p> 
					<p style="padding-left: 30px;">Id: `+ptr[0]+
					`<br />Tipo: ` +ptr[1]+
					`<br />Valor: ` +ptr[2]+`</p>`;
				}
				htmlText = htmlText + `</body>
								</html>`;
				panel.webview.html = htmlText;
			}
		});

			serverData.webview.onDidReceiveMessage(
				message => {
					switch(message.command){
						case 'start':
							console.log(message.text);
							socket.write(message.text); //CREA CONEXIÓN
							return;
						case 'leak':
							vscode.window.showInformationMessage('No se recibieron los datos necesarios');
						case 'stop':
							console.log(message.text);
							socket.write(message.text); //DETENER CONEXIÓN CON REMOTE MEMORY
						case 'test':
							console.log(message.text);
							var userValues = ''+message.text;
							var elements = userValues.split(",");
							console.log(userValues);
							fs.readFile('./conexiones.json', 'utf8', (err, jsonString) => {
								if (err) {
									console.log("File read failed:", err)
									return
								}
								console.log('File data:', jsonString)
								try {
									const customer = JSON.parse(jsonString)
									console.log("Customer address is:", customer.conexiones) // => "Customer address is: Infinity Loop Drive"
									customer['conexiones'].push({"usuario":''+elements[1],"contraseña":''+elements[2],"ip":''+elements[3],"puerto":''+elements[4]});
									const jsonStr = JSON.stringify(customer);
									console.log(jsonStr);
									updateJSON(jsonStr);
								} catch(err) {
									console.log('Error parsing JSON string:', err)
								} 
							})
							socket.write(message.text); //ENVÍA DATOS Y PRUEBA LA CONEXIÓN
					}
				},
				undefined,
				context.subscriptions
			);
			socket.on('end', function() {
				console.log('Closing connection with the socket');
			});
			// Don't forget to catch error, for your own sake.
			socket.on('error', function(err) {
				console.log(`Error: ${err}`);
			});
		});
		
		/*fs.readFile('./conexiones.json', 'utf8', (err, jsonString) => {
			if (err) {
				console.log("File read failed:", err)
				return
			}
			console.log('File data:', jsonString)
			try {
				const customer = JSON.parse(jsonString)
				console.log("Customer address is:", customer.conexiones) // => "Customer address is: Infinity Loop Drive"
				customer['conexiones'].push({"usuario":"Carlos","contraseña":"1346","ip":"127.0.0.1","puerto":"69"});
				const jsonStr = JSON.stringify(customer);
				console.log(jsonStr);
				updateJSON(jsonStr);
			} catch(err) {
				console.log('Error parsing JSON string:', err)
			} 
		})*/
		console.log(vscode.Location.name);
		const panel = vscode.window.createWebviewPanel('memoryManager', 
		'Memory Manager',vscode.ViewColumn.One,{});
		
		const serverData = vscode.window.createWebviewPanel('datosConexion', 
		'Datos de conexion',vscode.ViewColumn.One,{
			enableScripts:true
		});
		
		serverData.webview.html = serverInfo;
		

		vscode.window.showInformationMessage('Hello World from memoryM!');
		
	});
	
	context.subscriptions.push(disposable);
}

exports.activate = activate;

const serverInfo = `<!DOCTYPE html> 
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Datos de conexión</title>
	<script type = "text/javascript">
	const vscode = acquireVsCodeApi();
	function conectionData(){
		vscode.postMessage({
			command: 'start',
			text: "start"
			})
		
	}

	function probar(){
		const user = document.getElementById('user').value;
		const password = document.getElementById('password').value;
		const ip = document.getElementById('ip').value;
		const port = document.getElementById('port').value;
		console.log(user);
		if(user != "" && password != "" && ip != "" && port != ""){
			vscode.postMessage({
				command: 'test',
				text: "true,"+user +","+ password +","+ ip +","+ port
			})
		}else{
			vscode.postMessage({
				command: 'leak',
				text: ""
			})
		}
	}

	function stop(){
		console.log("algo");
		vscode.postMessage({
			command: 'stop',
			text: "stop"
			})
	}

	</script>
</head>
<body>
	<form id="form" onSubmit="JavaScript:conectionData()">
		<label for="user">Nombre de usuario:</label><br>
		<input type="text" id="user" name="user" value=""><br>
		<label for="password">Contraseña:</label><br>
		<input type="password" id="password" name="password" value=""><br>
		<label for="ip">IP:</label><br>
		<input type="text" id="ip" name="ip" value=""><br>
		<label for="port">Puerto:</label><br>
		<input type="text" id="port" name="port" value=""><br><br>
		<input type="submit" value="Aceptar">
		<input type="reset" onClick="stop()">
		<input type="button" value="Probar conexión" onClick="probar()">
		</form> 
</body>
</html>`;
// this method is called when your extension is deactivated
function deactivate() {}

module.exports = {
	activate,
	deactivate
}

function obtainJson(path) {
	fs.readFile(path, 'utf8', (err, jsonString) => {
		if (err) {
			console.log("Error reading file from disk:", err)
			return
		}
		try {
			const customer = JSON.parse(jsonString)
			return customer;
		} catch(err) {
			console.log('Error parsing JSON string:', err)
		}
	})
}

function updateJSON(jsonString) {
	fs.writeFile('./conexiones.json', jsonString, err => {
		if (err) {
			console.log('Error writing file', err)
		} else {
			console.log('Successfully wrote file')
		}
	})
}