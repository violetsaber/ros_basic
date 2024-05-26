// Auto-generated. Do not edit!

// (in-package plumbing_pub_sub_doublemsg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let pose1 = require('./pose1.js');

//-----------------------------------------------------------

class pose2 {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vel = null;
      this.ang = null;
    }
    else {
      if (initObj.hasOwnProperty('vel')) {
        this.vel = initObj.vel
      }
      else {
        this.vel = new pose1();
      }
      if (initObj.hasOwnProperty('ang')) {
        this.ang = initObj.ang
      }
      else {
        this.ang = new pose1();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pose2
    // Serialize message field [vel]
    bufferOffset = pose1.serialize(obj.vel, buffer, bufferOffset);
    // Serialize message field [ang]
    bufferOffset = pose1.serialize(obj.ang, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pose2
    let len;
    let data = new pose2(null);
    // Deserialize message field [vel]
    data.vel = pose1.deserialize(buffer, bufferOffset);
    // Deserialize message field [ang]
    data.ang = pose1.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'plumbing_pub_sub_doublemsg/pose2';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4b494f3bb942b17882f6ddc15759053f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    pose1 vel
    pose1 ang
    ================================================================================
    MSG: plumbing_pub_sub_doublemsg/pose1
    float32 x
    float32 y
    float32 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pose2(null);
    if (msg.vel !== undefined) {
      resolved.vel = pose1.Resolve(msg.vel)
    }
    else {
      resolved.vel = new pose1()
    }

    if (msg.ang !== undefined) {
      resolved.ang = pose1.Resolve(msg.ang)
    }
    else {
      resolved.ang = new pose1()
    }

    return resolved;
    }
};

module.exports = pose2;
