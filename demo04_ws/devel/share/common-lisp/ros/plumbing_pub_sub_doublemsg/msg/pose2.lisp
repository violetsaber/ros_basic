; Auto-generated. Do not edit!


(cl:in-package plumbing_pub_sub_doublemsg-msg)


;//! \htmlinclude pose2.msg.html

(cl:defclass <pose2> (roslisp-msg-protocol:ros-message)
  ((vel
    :reader vel
    :initarg :vel
    :type plumbing_pub_sub_doublemsg-msg:pose1
    :initform (cl:make-instance 'plumbing_pub_sub_doublemsg-msg:pose1))
   (ang
    :reader ang
    :initarg :ang
    :type plumbing_pub_sub_doublemsg-msg:pose1
    :initform (cl:make-instance 'plumbing_pub_sub_doublemsg-msg:pose1)))
)

(cl:defclass pose2 (<pose2>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pose2>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pose2)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name plumbing_pub_sub_doublemsg-msg:<pose2> is deprecated: use plumbing_pub_sub_doublemsg-msg:pose2 instead.")))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <pose2>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader plumbing_pub_sub_doublemsg-msg:vel-val is deprecated.  Use plumbing_pub_sub_doublemsg-msg:vel instead.")
  (vel m))

(cl:ensure-generic-function 'ang-val :lambda-list '(m))
(cl:defmethod ang-val ((m <pose2>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader plumbing_pub_sub_doublemsg-msg:ang-val is deprecated.  Use plumbing_pub_sub_doublemsg-msg:ang instead.")
  (ang m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pose2>) ostream)
  "Serializes a message object of type '<pose2>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'vel) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ang) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pose2>) istream)
  "Deserializes a message object of type '<pose2>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'vel) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ang) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pose2>)))
  "Returns string type for a message object of type '<pose2>"
  "plumbing_pub_sub_doublemsg/pose2")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pose2)))
  "Returns string type for a message object of type 'pose2"
  "plumbing_pub_sub_doublemsg/pose2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pose2>)))
  "Returns md5sum for a message object of type '<pose2>"
  "4b494f3bb942b17882f6ddc15759053f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pose2)))
  "Returns md5sum for a message object of type 'pose2"
  "4b494f3bb942b17882f6ddc15759053f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pose2>)))
  "Returns full string definition for message of type '<pose2>"
  (cl:format cl:nil "pose1 vel~%pose1 ang~%================================================================================~%MSG: plumbing_pub_sub_doublemsg/pose1~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pose2)))
  "Returns full string definition for message of type 'pose2"
  (cl:format cl:nil "pose1 vel~%pose1 ang~%================================================================================~%MSG: plumbing_pub_sub_doublemsg/pose1~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pose2>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'vel))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ang))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pose2>))
  "Converts a ROS message object to a list"
  (cl:list 'pose2
    (cl:cons ':vel (vel msg))
    (cl:cons ':ang (ang msg))
))
