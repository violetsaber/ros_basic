;; Auto-generated. Do not edit!


(when (boundp 'plumbing_pub_sub_doublemsg::pose2)
  (if (not (find-package "PLUMBING_PUB_SUB_DOUBLEMSG"))
    (make-package "PLUMBING_PUB_SUB_DOUBLEMSG"))
  (shadow 'pose2 (find-package "PLUMBING_PUB_SUB_DOUBLEMSG")))
(unless (find-package "PLUMBING_PUB_SUB_DOUBLEMSG::POSE2")
  (make-package "PLUMBING_PUB_SUB_DOUBLEMSG::POSE2"))

(in-package "ROS")
;;//! \htmlinclude pose2.msg.html


(defclass plumbing_pub_sub_doublemsg::pose2
  :super ros::object
  :slots (_vel _ang ))

(defmethod plumbing_pub_sub_doublemsg::pose2
  (:init
   (&key
    ((:vel __vel) (instance plumbing_pub_sub_doublemsg::pose1 :init))
    ((:ang __ang) (instance plumbing_pub_sub_doublemsg::pose1 :init))
    )
   (send-super :init)
   (setq _vel __vel)
   (setq _ang __ang)
   self)
  (:vel
   (&rest __vel)
   (if (keywordp (car __vel))
       (send* _vel __vel)
     (progn
       (if __vel (setq _vel (car __vel)))
       _vel)))
  (:ang
   (&rest __ang)
   (if (keywordp (car __ang))
       (send* _ang __ang)
     (progn
       (if __ang (setq _ang (car __ang)))
       _ang)))
  (:serialization-length
   ()
   (+
    ;; plumbing_pub_sub_doublemsg/pose1 _vel
    (send _vel :serialization-length)
    ;; plumbing_pub_sub_doublemsg/pose1 _ang
    (send _ang :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; plumbing_pub_sub_doublemsg/pose1 _vel
       (send _vel :serialize s)
     ;; plumbing_pub_sub_doublemsg/pose1 _ang
       (send _ang :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; plumbing_pub_sub_doublemsg/pose1 _vel
     (send _vel :deserialize buf ptr-) (incf ptr- (send _vel :serialization-length))
   ;; plumbing_pub_sub_doublemsg/pose1 _ang
     (send _ang :deserialize buf ptr-) (incf ptr- (send _ang :serialization-length))
   ;;
   self)
  )

(setf (get plumbing_pub_sub_doublemsg::pose2 :md5sum-) "4b494f3bb942b17882f6ddc15759053f")
(setf (get plumbing_pub_sub_doublemsg::pose2 :datatype-) "plumbing_pub_sub_doublemsg/pose2")
(setf (get plumbing_pub_sub_doublemsg::pose2 :definition-)
      "pose1 vel
pose1 ang
================================================================================
MSG: plumbing_pub_sub_doublemsg/pose1
float32 x
float32 y
float32 z
")



(provide :plumbing_pub_sub_doublemsg/pose2 "4b494f3bb942b17882f6ddc15759053f")


