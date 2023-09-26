const express = require('express');
const app = express();
var AWS = require("aws-sdk");
const fs = require("fs");


 //AWS DynamoDB Connection

 let awsConfig = {
    "region": "us-east-1",
    "endpoint": "dynamodb.us-east-1.amazonaws.com",
    "accessKeyId": process.env.ACCESS_KEY, 
    "secretAccessKey": process.env.SECRET_ACCESS_KEY
};

AWS.config.update(awsConfig);
let docClient = new AWS.DynamoDB.DocumentClient();
      
//Sensor Data

try{

    const iotData = fs.readFileSync("C:/Users/KAVIUL/Desktop/Sensor_data.json").toString('utf-8')
    const jsonString = JSON.stringify(iotData);
    console.log(jsonString);

       //AWS Data

       let save = function () {

        var input = {
            "entry_id": jsonString.entry_id, "created_at": jsonString.created_at, "LDR": jsonString.field1,
            "PIR": jsonString.field2, "Light": jsonString.field3, "Switch": jsonString.field4
        };
      
        var params = {
            TableName: "SIT729_IoT_Table",
            Item:  input, 
        
        };
        docClient.put(params, function (err, data) {
    
            if (err) {
                console.log("users::save::error - " + JSON.stringify(err, null, 2));                      
            } else {
                console.log("users::save::success" );                      
            }
            
        });
    }
    
    save();


}  catch (error) {
    console.error('Error in sensortest:', error);
   
}

      


