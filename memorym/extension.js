// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require('vscode');
const net = require('net');
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
	let disposable = vscode.commands.registerCommand('memorym.helloWorld', function () {
		
		// The code you place here will be executed every time your command is executed

		// Display a message box to the user


		var Client = net.createConnection;
		var client = Client({port: 54000, localAddress: '127.0.0.1', localPort: 51000});
		var datos = " ";
		
		

		client.on('connect', function() {
		var id = this.localAddress + ': ' + this.localPort;
		console.log('Client connected', id);
		client.write("$i2342*")
		});

		
		var htmlText = `<!DOCTYPE html>
		<html lang="en">
		<head>
			<meta charset="UTF-8">
			<meta name="viewport" content="width=device-width, initial-scale=1.0">
			<title>Memory Remote</title>
		</head>
		<body>`;

		client.on('data', function (data) {
			datos = ''+data;
			console.log('Received: '+ data);
			if(datos == "error"){
				vscode.window.showInformationMessage("Error: no se logró crear la conexión");
			}if(datos == "success"){
				vscode.window.showInformationMessage("Se logró crear la conexión con el servidor");
			}else{
				var valores = datos.split(',');
				if(valores[0]== "0"){
					htmlText+=`<p>Variable `+valores[1].toString() + `</p> 
					<p style="padding-left: 30px;">Tipo: `+valores[2]+
					`<br />Valor: ` +valores[3]+
					`<br />Celda de memoria: ` +valores[4]+
					`<br />Referencias actuales: ` +valores[5]+`</p>`;
				}else if(valores[0] == "1"){
					htmlText+=`<p>Puntero `+valores[1].toString() + `</p> 
					<p style="padding-left: 30px;">Id: `+valores[1]+
					`<br />Tipo: ` +valores[2]+
					`<br />Valor: ` +valores[3]+`</p>`;
				}else if(datos.endsWith(";")){

					htmlText += `</body>
								</html>`;
					panel.webview.html = htmlText;
				}
			}
		});

		const panel = vscode.window.createWebviewPanel('memoryManager', 
		'Memory Manager',vscode.ViewColumn.One,{});
		
		const serverData = vscode.window.createWebviewPanel('datosConexion', 
		'Datos de conexion',vscode.ViewColumn.One,{
			enableScripts:true
		});
		
		serverData.webview.html = serverInfo;
		serverData.webview.onDidReceiveMessage(
			message => {
				switch(message.command){
					case 'data':
						console.log(message.text);
						//client.write(message.text); ENVIAR DATOS AL SERVIDOR 
						return;
					case 'leak':
						vscode.window.showInformationMessage('No se recibieron los datos necesarios');
					case 'stop':
						console.log(message.text);
						//client.write(message.text); DETENER CONEXIÓN CON REMOTE MEMORY
				}
			},
			undefined,
			context.subscriptions
		);

		vscode.window.showInformationMessage('Hello World from memoryM!');
		
	});
	
	context.subscriptions.push(disposable);
}
exports.activate = activate;

//FALTA INCORPORARA FUNCIÓN RESET
const serverInfo = `<!DOCTYPE html> 
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Datos de conexión</title>
	<script type = "text/javascript">
	function conectionData(){
		const vscode = acquireVsCodeApi();
		const user = document.getElementById('user').value;
		const password = document.getElementById('password').value;
		const ip = document.getElementById('ip').value;
		const port = document.getElementById('port').value;
		console.log(user);
		if(user != "" && password != "" && ip != "" && port != ""){
			vscode.postMessage({
				command: 'data',
				text: "true,"+user +","+ password +","+ ip +","+ port
			})
		}else{
			vscode.postMessage({
				command: 'leak',
				text: ""
			})
		}
	}
	function killConection(){
		const vscode = acquireVsCodeApi();
		vscode.postMessage({
			command: 'stop',
			text: "false,0,0,0,0"
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
		<input type="reset">
		</form> 
</body>
</html>`;
// this method is called when your extension is deactivated
function deactivate() {}

module.exports = {
	activate,
	deactivate
}
