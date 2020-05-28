// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require('vscode');
const net = require('net');
const ffi = require('ffi-napi');

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
		client.write("$i")
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

			var pkgs = datos.split('&')[0].split(".");
			var cantidadpkgs = pkgs.length;
			
			var ptrs = datos.split('&')[1].split(".");
			var cantidadptrs = ptrs.length;
			for(let i = 0; i<cantidadpkgs; i++){
				var temp = pkgs[i].split(',')
				htmlText+=`<p>Variable `+i.toString() + `</p> 
				<p style="padding-left: 30px;">Tipo: `+temp[1]+
				`<br />Valor: ` +temp[2]+
				`<br />Celda de memoria: ` +temp[3]+
				`<br />Referencias actuales: ` +temp[4]+`</p>`;
			}
			for(let i = 0; i<cantidadptrs; i++){
				var temp = ptrs[i].split(',')
				htmlText+=`<p>Puntero `+i.toString() + `</p> 
				<p style="padding-left: 30px;">Id: `+temp[0]+
				`<br />Tipo: ` +temp[1]+
				`<br />Valor: ` +temp[2]+`</p>`;
			}htmlText += `</body>
							</html>`;
			panel.webview.html = htmlText;
		});

		const panel = vscode.window.createWebviewPanel('memoryManager', 
		'Memory Manager',vscode.ViewColumn.One,{});
		
		
		vscode.window.showInformationMessage('Hello World from memoryM!');
		
	});
	
	context.subscriptions.push(disposable);
}
exports.activate = activate;

// this method is called when your extension is deactivated
function deactivate() {}

module.exports = {
	activate,
	deactivate
}
