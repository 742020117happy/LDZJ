var path = 'C:/Users/Administrator/Desktop/Robot_App/轮对质检/煜禾森/Magic商业导航接口-v1.4.4.json';
var d = require(path);
var fs = require('fs');

function repeat(s, n) {
    var r = '';
    for (var i = 0; i < n; i++) r += s;
    return r;
}

var out = '';

// ============ ENVIRONMENTS ============
out += '========================================\n';
out += 'ENVIRONMENTS (' + d.global.envs.length + ')\n';
out += '========================================\n\n';
d.global.envs.forEach(function(e) {
    out += '  Name: ' + e.name + ' (ID: ' + e.env_id + ')\n';
    e.server_list.forEach(function(s) {
        out += '    Server: ' + s.name + ' -> ' + s.uri + '\n';
    });
    out += '\n';
});

// ============ FOLDERS ============
var folders = d.apis.filter(function(a) { return a.target_type == 'folder'; });
var folderMap = {};
folders.forEach(function(f) { folderMap[f.target_id] = f; });

// ============ API TREE ============
out += '\n========================================\n';
out += 'API ENDPOINTS BY MODULE (' + d.apis.length + ' total entries)\n';
out += '========================================\n\n';

function buildTree(pid, depth) {
    var r = '';
    var children = d.apis.filter(function(a) { return a.parent_id == pid; });
    children.sort(function(a, b) { return (a.sort || 0) - (b.sort || 0); });
    children.forEach(function(c) {
        var indent = repeat('  ', depth);
        if (c.target_type == 'folder') {
            r += indent + '----------------------------------------\n';
            r += indent + 'MODULE: ' + c.name + ' (ID: ' + c.target_id + ')\n';
            r += indent + '----------------------------------------\n';
            r += buildTree(c.target_id, depth + 1);
            r += '\n';
        } else if (c.target_type == 'api') {
            r += indent + '--- API ---\n';
            r += indent + '  Name: ' + c.name + '\n';
            r += indent + '  ID: ' + c.target_id + '\n';
            r += indent + '  Method: ' + c.method + '\n';
            r += indent + '  URL: ' + c.url + '\n';
            if (c.description) r += indent + '  Description: ' + c.description + '\n';
            
            // Request parameters
            if (c.request) {
                var body = c.request.body || {};
                r += indent + '  Request Body Mode: ' + (body.mode || 'none') + '\n';
                
                var params = [];
                if (c.request.query && c.request.query.parameter && c.request.query.parameter.length > 0) {
                    c.request.query.parameter.forEach(function(p) {
                        p.in = 'query';
                        params.push(p);
                    });
                }
                if (c.request.header && c.request.header.parameter && c.request.header.parameter.length > 0) {
                    c.request.header.parameter.forEach(function(p) {
                        p.in = 'header';
                        params.push(p);
                    });
                }
                if (c.request.restful && c.request.restful.parameter && c.request.restful.parameter.length > 0) {
                    c.request.restful.parameter.forEach(function(p) {
                        p.in = 'path';
                        params.push(p);
                    });
                }
                if (body.parameter && body.parameter.length > 0) {
                    body.parameter.forEach(function(p) {
                        p.in = 'body';
                        params.push(p);
                    });
                }
                
                if (params.length > 0) {
                    r += indent + '  Request Parameters:\n';
                    params.forEach(function(p) {
                        var req = (p.required || p.is_checked) ? '[REQUIRED]' : '[optional]';
                        var type = p.type || p.data_type || 'string';
                        r += indent + '    [' + p.in + '] ' + p.name + ' (' + type + ') ' + req + '\n';
                        if (p.description) r += indent + '      Description: ' + p.description + '\n';
                        if (p.value !== undefined && p.value !== null && p.value !== '') r += indent + '      Default/Example: ' + JSON.stringify(p.value) + '\n';
                    });
                }
                
                // Raw request body
                if (body.raw && body.raw.trim()) {
                    var rawStr = body.raw.substring(0, 500);
                    r += indent + '  Request Body (raw):\n';
                    r += indent + '    ' + rawStr.replace(/\n/g, '\n' + indent + '    ') + '\n';
                }
            }
            
            // Response
            if (c.response && c.response.example && c.response.example.length > 0) {
                var ex = c.response.example[0];
                if (ex.raw) {
                    var resStr = ex.raw.substring(0, 500);
                    r += indent + '  Response Example:\n';
                    r += indent + '    ' + resStr.replace(/\n/g, '\n' + indent + '    ') + '\n';
                }
            }
            
            r += '\n';
        }
    });
    return r;
}

var tree = buildTree('0', 0);
out += tree;

// Write output
var outFile = 'C:/Users/Administrator/Desktop/Robot_App/轮对质检/煜禾森/api_extracted_summary.txt';
fs.writeFileSync(outFile, out, 'utf8');
console.log('Written to: ' + outFile);
console.log('Total size: ' + out.length + ' chars');
